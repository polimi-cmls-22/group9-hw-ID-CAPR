/*
  ==============================================================================

    PanProcessor.cpp
    Created: 28 May 2022 10:38:41pm
    Author:  claud

  ==============================================================================
*/

#include "PanProcessor.h"

PanProcessor::PanProcessor()
{
    pan.setRule(juce::dsp::PannerRule::linear);
}

void PanProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    pan.prepare(spec);
}

void PanProcessor::updateParameters(float newPan)
{
    pan.setPan(newPan);
}

void PanProcessor::updateOscParameter(float oscParameter)
{
    pan.setPan(oscParameter);
}

void PanProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    pan.process(context);
}

void PanProcessor::reset()
{
    pan.reset();
}
