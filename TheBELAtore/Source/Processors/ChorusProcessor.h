/*
  ==============================================================================

    ChorusProcessor.h
    Created: 23 May 2022 10:04:48am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class ChorusProcessor : public ProcessorBase
{
public:
    ChorusProcessor() {};
    ~ChorusProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float rate, float depth, float centreDelay, float feedback, float mix);
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    void updateOscParameter(float oscParameter) override;
    const juce::String getName() const override { return "Chorus"; };
private:
    juce::dsp::Chorus<float> chorus;
};