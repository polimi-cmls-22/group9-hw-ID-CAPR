/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 23 May 2022 10:04:21am
    Author:  claud

  ==============================================================================
*/

#include "ReverbProcessor.h"

ReverbProcessor::ReverbProcessor() 
{
    lowpass.setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
    highpass.setType(juce::dsp::FirstOrderTPTFilterType::highpass);
}

void ReverbProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };

    reverbParams.roomSize = 50.0f / 100.0f;
    reverbParams.width = 100.0f / 100.0f;
    reverbParams.damping = 50.0f / 100.0f;
    reverbParams.freezeMode = 0.0f;
    reverbParams.wetLevel = 50.0f / 100.0f;
    reverbParams.dryLevel = 1.0f - reverbParams.wetLevel;
    reverb.setParameters(reverbParams);
    reverb.prepare(spec);
    lowpass.setCutoffFrequency(22000.0f);
    highpass.setCutoffFrequency(20.0f);
    lowpass.prepare(spec);
    highpass.prepare(spec);

}

void ReverbProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
    lowpass.process(context);
    highpass.process(context);
}

void ReverbProcessor::reset()
{
    reverb.reset();
}

void ReverbProcessor::updateParameters(float roomSize, float width, float damping, float freeze, float mix, float lpfFreq, float hpfFreq)
{
    reverbParams.roomSize = roomSize;
    reverbParams.width = width;
    reverbParams.damping = damping;
    reverbParams.freezeMode = freeze;
    reverbParams.wetLevel = mix;
    reverbParams.dryLevel = 1.0f - mix;
    reverb.setParameters(reverbParams);


    lowpass.setCutoffFrequency(lpfFreq);
    highpass.setCutoffFrequency(hpfFreq);
}

void ReverbProcessor::updateOscParameter(float oscParameter) 
{
    reverbParams.wetLevel = oscParameter;
    reverb.setParameters(reverbParams);
}
