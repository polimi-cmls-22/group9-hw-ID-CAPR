/*
  ==============================================================================

    PhaserProcessor.h
    Created: 23 May 2022 10:06:26am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class PhaserProcessor : public ProcessorBase
{
public:
    PhaserProcessor() {};
    ~PhaserProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void updateOscParameter(float oscParameter) override;
    void reset() override;
    void updateParameters(float rate, float depth, float centreFrequency, float feedback, float mix);
    const juce::String getName() const override { return "Phaser"; }

private:
    juce::dsp::Phaser<float> phaser;
};