/*
  ==============================================================================

    ReverbProcessor.h
    Created: 23 May 2022 10:04:21am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class ReverbProcessor : public ProcessorBase
{
public:
    ReverbProcessor();
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void reset() override;
    void updateParameters(float roomSize, float width, float damping, float freeze, float mix, float lpfFreq, float hpfFreq);
    void updateOscParameter(float oscParameter) override;
    const juce::String getName() const override { return "Reverb"; };
private:
    juce::dsp::Reverb reverb;
    juce::Reverb::Parameters reverbParams;
    juce::dsp::FirstOrderTPTFilter<float> lowpass;
    juce::dsp::FirstOrderTPTFilter<float> highpass;
};