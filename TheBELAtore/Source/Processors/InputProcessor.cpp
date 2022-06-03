/*
  ==============================================================================

    InputProcessor.cpp
    Created: 28 May 2022 10:51:52am
    Author:  claud

  ==============================================================================
*/

#include "InputProcessor.h"

InputProcessor::InputProcessor()
{
    inputGain.setGainDecibels(0.0f);
}

void InputProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    inputGain.setRampDurationSeconds(0.05);;
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    inputGain.prepare(spec);
}

void InputProcessor::updateParameters(float inGaindB)
{
    inputGain.setGainDecibels(inGaindB);
}

void InputProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    inputGain.process(context);
}

void InputProcessor::reset()
{
    inputGain.reset();
}
