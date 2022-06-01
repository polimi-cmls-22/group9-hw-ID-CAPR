/*
  ==============================================================================

    MasterProcessor.cpp
    Created: 28 May 2022 10:52:00am
    Author:  claud

  ==============================================================================
*/

#include "MasterProcessor.h"

MasterProcessor::MasterProcessor()
{
    masterGain.setGainDecibels(0.0f);
}

void MasterProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    masterGain.setRampDurationSeconds(0.05);;
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    masterGain.prepare(spec);
}

void MasterProcessor::updateParameters(float outGaindB)
{
    masterGain.setGainDecibels(outGaindB);
}

void MasterProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    masterGain.process(context);
}

void MasterProcessor::reset()
{
    masterGain.reset();
}
