/*
  ==============================================================================

    PhaserProcessor.cpp
    Created: 23 May 2022 10:06:26am
    Author:  claud

  ==============================================================================
*/

#include "PhaserProcessor.h"

void PhaserProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    phaser.reset();
    phaser.setMix(0.5f);
    phaser.setCentreFrequency(600.0f);
    phaser.setRate(1.0f);
    phaser.setDepth(0.5f);
    phaser.setFeedback(0.5f);
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    phaser.prepare(spec);
}

void PhaserProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    phaser.process(context);
}

void PhaserProcessor::updateOscParameter(float oscParameter)
{
    phaser.setMix(oscParameter);
}

void PhaserProcessor::reset()
{
    phaser.reset();
}

void PhaserProcessor::updateParameters(float rate, float depth, float centreFrequency, float feedback, float mix)
{
    phaser.setRate(rate);
    phaser.setDepth(depth);
    phaser.setCentreFrequency(centreFrequency);
    phaser.setFeedback(feedback);
    phaser.setMix(mix);
}
