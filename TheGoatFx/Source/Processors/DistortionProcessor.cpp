/*
  ==============================================================================

    OverdriveProcessor.cpp
    Created: 23 May 2022 11:56:33am
    Author:  claud

  ==============================================================================
*/

#include "DistortionProcessor.h"


DistortionProcessor::DistortionProcessor()
{
    auto& waveshaper = distortionChain.template get<waveshaperIndex>(); 

    waveshaper.functionToUse = [](float x)
    {
        return std::tanh(x);
    };

    auto& distGain = distortionChain.template get<distortionGainIndex>();
    distGain.setGainDecibels(0.0f);

    auto& compGain = distortionChain.template get<compensationGainIndex>();
    compGain.setGainDecibels(0.0f);

    auto& lowpass = distortionChain.template get <lpfIndex>();
    lowpass.setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
    lowpass.setCutoffFrequency(22000.0f);

    auto& highpass = distortionChain.template get <hpfIndex>();
    highpass.setType(juce::dsp::FirstOrderTPTFilterType::highpass);
    highpass.setCutoffFrequency(20.0f);

    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);

    selectAmp(0);
}


void DistortionProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), getTotalNumOutputChannels() };
    distortionChain.prepare(spec);
    mixer.prepare(spec);
}

void DistortionProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    if (context.isBypassed)
        return;
    mixer.pushDrySamples(block);
    distortionChain.process(context);
    mixer.mixWetSamples(block);
}


void DistortionProcessor::reset()
{
    distortionChain.reset();
}

void DistortionProcessor::updateOscParameter(float oscParameter)
{
    mixer.setWetMixProportion(oscParameter);
}

void DistortionProcessor::selectAmp(int ampIndex)
{
        auto dir = juce::File::getCurrentWorkingDirectory();

        int numTries = 0;

        while (!dir.getChildFile("Resources").exists() && numTries++ < 15)
            dir = dir.getParentDirectory();

        auto& convolution = distortionChain.template get<cabinetIndex>();
        juce::String amp;
        switch (ampIndex)
        {
        case 0:
            amp = "Bugera V55 Infinium SM57.wav";
            break;
        case 1:
            amp = "Fender Frontman 212 SM57.wav";
            break;
        case 2:
            amp = "Marshall 1960VB SM57.wav";
            break;
        case 3:
            amp = "Orange Crush CR60C SM57.wav";
            break;
        case 4:
            amp = "VOX AC15C1 SM57.wav";
            break;
        default: break;
           
        }
        convolution.loadImpulseResponse(dir.getChildFile("Resources").getChildFile(amp),
            juce::dsp::Convolution::Stereo::yes,
            juce::dsp::Convolution::Trim::no,
            1024);                                
}

void DistortionProcessor::updateParameters(float lpfCutoff, float hpfCutoff, float distGain, float compGain, int cabinetIndex, float mix)
{
    juce::dsp::get<lpfIndex>(distortionChain).setCutoffFrequency(lpfCutoff);
    juce::dsp::get<hpfIndex>(distortionChain).setCutoffFrequency(hpfCutoff);
    juce::dsp::get<distortionGainIndex>(distortionChain).setGainDecibels(distGain);
    juce::dsp::get<compensationGainIndex>(distortionChain).setGainDecibels(compGain);
    selectAmp(cabinetIndex);
    mixer.setWetMixProportion(mix);
}
