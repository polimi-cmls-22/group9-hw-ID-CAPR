#pragma once
/*
  ==============================================================================

    InputProcessor.h
    Created: 23 May 2022 10:05:52am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class InputProcessor : public ProcessorBase
{
public:
    InputProcessor();
    ~InputProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float inGaindB);
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Input"; };

private:
    juce::dsp::Gain<float> inputGain;

};
