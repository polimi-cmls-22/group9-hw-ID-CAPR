/*
  ==============================================================================

    FilterProcessor.h
    Created: 23 May 2022 10:05:52am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class FilterProcessor : public ProcessorBase
{
public:
    FilterProcessor();
    ~FilterProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float frequency, float newLowGain, float newHighGain);
    void updateOscParameter(float oscParameter) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Filter"; };

private:

    juce::dsp::LinkwitzRileyFilter<float> lowpass, highpass;
    juce::dsp::Gain<float> lowGain, highGain;
    juce::AudioBuffer<float> bufferSeparation;

};
