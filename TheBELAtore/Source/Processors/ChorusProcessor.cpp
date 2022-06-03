/*
  ==============================================================================

    ChorusProcessor.cpp
    Created: 23 May 2022 10:04:48am
    Author:  claud

  ==============================================================================
*/


#include "ChorusProcessor.h"


void ChorusProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    chorus.reset();
    chorus.setMix(0.5f);
    chorus.setCentreDelay(7.0f);
    chorus.setRate(1.0f);
    chorus.setFeedback(0.5f);
    chorus.setDepth(0.5f);
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    chorus.prepare(spec);
}

void ChorusProcessor::updateParameters(float rate, float depth, float centreDelay, float feedback, float mix)
{
    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(centreDelay);
    chorus.setFeedback(feedback);
    chorus.setMix(mix);
}


void ChorusProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);
}

void ChorusProcessor::reset()
{
    chorus.reset();
}

void ChorusProcessor::updateOscParameter(float oscParameter)
{
    chorus.setMix(oscParameter);
}
