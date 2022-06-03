/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 23 May 2022 10:05:52am
    Author:  claud

  ==============================================================================
*/

#include "FilterProcessor.h"

FilterProcessor::FilterProcessor()
{
    lowGain.setRampDurationSeconds(0.05);
    highGain.setRampDurationSeconds(0.05);

    lowpass.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    highpass.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    lowpass.setCutoffFrequency(2000.0f);
    highpass.setCutoffFrequency(2000.0f);
    lowGain.setGainDecibels(0.0f);
    highGain.setGainDecibels(0.0f);
}

void FilterProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lowpass.reset();
    highpass.reset();
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    lowpass.prepare(spec);
    highpass.prepare(spec);
    lowGain.prepare(spec);
    highGain.prepare(spec);
    bufferSeparation.setSize(4, int(spec.maximumBlockSize), false, false, true);
}

void FilterProcessor::updateParameters(float frequency, float newLowGain, float newHighGain)
{
    lowpass.setCutoffFrequency(frequency);
    highpass.setCutoffFrequency(frequency);
    lowGain.setGainDecibels(newLowGain);
    highGain.setGainDecibels(newHighGain);
}

void FilterProcessor::updateOscParameter(float oscParameter)
{
    lowpass.setCutoffFrequency(oscParameter);
    highpass.setCutoffFrequency(oscParameter);
}

void FilterProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    const auto inputBlock = context.getInputBlock();
    const auto numSamples = inputBlock.getNumSamples();
    const auto numChannels = inputBlock.getNumChannels();

    //Separation of the blocks in order to process separately low frequencies and high frequencies
    auto sepBlock = juce::dsp::AudioBlock<float>(bufferSeparation).getSubBlock(0, (size_t)numSamples);

    auto sepLowBlock = sepBlock.getSubsetChannelBlock(0, (size_t)numChannels);
    auto sepHighBlock = sepBlock.getSubsetChannelBlock(2, (size_t)numChannels);

    sepLowBlock.copyFrom(inputBlock);
    sepHighBlock.copyFrom(inputBlock);

    //two separate context that will be processed by filter and gain
    auto contextLow = juce::dsp::ProcessContextReplacing<float>(sepLowBlock);
    contextLow.isBypassed = context.isBypassed;
    lowpass.process(contextLow);
    lowGain.process(contextLow);

    auto contextHigh = juce::dsp::ProcessContextReplacing<float>(sepHighBlock);
    contextHigh.isBypassed = context.isBypassed;
    highpass.process(contextHigh);
    highGain.process(contextHigh);

    if (!context.isBypassed)
    {
        sepLowBlock.add(sepHighBlock);
        context.getOutputBlock().copyFrom(sepLowBlock);
    }

}

void FilterProcessor::reset()
{
    lowpass.reset();
    highpass.reset();
    lowGain.reset();
    highGain.reset();
}
