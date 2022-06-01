/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 23 May 2022 11:56:48am
    Author:  claud

  ==============================================================================
*/

#include "DelayProcessor.h"

DelayProcessor::DelayProcessor()
{
    smoothFilter.setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
    lowpass.setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);

    smoothFilter.setCutoffFrequency(1000.0 / 400.0f);
    lowpass.setCutoffFrequency(22000.0f);
    mixer.setWetMixProportion(0.5f);

}

void DelayProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };

    delayLine.prepare(spec);
    smoothFilter.prepare(spec);
    lowpass.prepare(spec);
    mixer.prepare(spec);

    for (auto& volume : delayFeedbackVolume)
        volume.reset(sampleRate, 0.05);

    std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f);
}

//==============================================================================

void DelayProcessor::reset() noexcept
{ 
    delayLine.reset();
    smoothFilter.reset();
    lowpass.reset();
    mixer.reset();
    std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f);
}

//==============================================================================

void DelayProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    if (context.isBypassed)
        return;

    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    const auto numChannels = juce::jmax(totalNumInputChannels, totalNumOutputChannels);

    const auto& inputBlock = context.getInputBlock().getSubsetChannelBlock(0, (size_t)numChannels);
    const auto& outputBlock = context.getOutputBlock();
    const auto numSamples = inputBlock.getNumSamples();

    mixer.pushDrySamples(inputBlock);

    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* samplesIn = inputBlock.getChannelPointer(channel);
        auto* samplesOut = outputBlock.getChannelPointer(channel);

        for (size_t i = 0; i < numSamples; ++i)
        {
            auto input = samplesIn[i] - lastDelayOutput[channel];

            auto delay = smoothFilter.processSample(int(channel), delayValue[channel]);

            const auto output = [&]
            {
                delayLine.pushSample(int(channel), input);
                delayLine.setDelay((float)delay < delaySamples ? (float)delay : delaySamples);
                return delayLine.popSample(int(channel));
            }();
            
            const auto processed = lowpass.processSample(int(channel), output);
            samplesOut[i] = processed;
            lastDelayOutput[channel] = processed * delayFeedbackVolume[channel].getNextValue();
        }
    }

    mixer.mixWetSamples(outputBlock);
}

void DelayProcessor::updateParameters(float value, float feedback, float smoothing, float lowpassCutoff, float mix)
{
    auto delayTime = (double)value / 1000.0 * getSampleRate();
    jassert(delayTime <= delaySamples);

    std::fill(delayValue.begin(),
        delayValue.end(),
        delayTime);

    for (auto& volume : delayFeedbackVolume)
        volume.setTargetValue(feedback);

    smoothFilter.setCutoffFrequency(1000.0f / smoothing);
    lowpass.setCutoffFrequency(lowpassCutoff);
    mixer.setWetMixProportion(mix / 100.0f);
}

void DelayProcessor::updateOscParameter(float oscParameter)
{
    mixer.setWetMixProportion(oscParameter);
}




