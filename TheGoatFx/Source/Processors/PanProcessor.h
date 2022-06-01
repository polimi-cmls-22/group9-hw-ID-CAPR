/*
  ==============================================================================

    PanProcessor.h
    Created: 28 May 2022 10:52:00am
    Author:  claud

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class PanProcessor : public ProcessorBase
{
public:
    PanProcessor();
    ~PanProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float pan);
    void updateOscParameter(float oscParameter) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Pan"; };

private:
    juce::dsp::Panner<float> pan;
};
