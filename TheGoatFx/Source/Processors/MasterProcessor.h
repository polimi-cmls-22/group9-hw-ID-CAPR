/*
  ==============================================================================

    MasterProcessor.h
    Created: 28 May 2022 10:52:00am
    Author:  claud

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class MasterProcessor : public ProcessorBase
{
public:
    MasterProcessor();
    ~MasterProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float outGaindB);
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Master"; };

private:
    juce::dsp::Gain<float> masterGain;

};
