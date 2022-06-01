/*
  ==============================================================================

    DelayProcessor.h
    Created: 23 May 2022 11:56:48am
    Author:  claud

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class DelayProcessor : public ProcessorBase
{
public:
    DelayProcessor();
    ~DelayProcessor() {};

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void updateParameters(float delayValue, float feedback,
        float smoothing, float lowpassCutoff, float mix);
    void updateOscParameter(float oscParameter) override;
    void reset() noexcept override;
    const juce::String getName() const override { return "Delay"; };

private:
    static constexpr auto delaySamples = 96000;

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine{ delaySamples };
    static const int maxNumChannels{ 2 };
    std::array<float, maxNumChannels> lastDelayOutput;

    juce::dsp::FirstOrderTPTFilter<double> smoothFilter;
    juce::dsp::FirstOrderTPTFilter<float> lowpass;
    int delayType = 1;

    std::array<double, maxNumChannels> delayValue {{}};
    std::array<juce::LinearSmoothedValue<float>, maxNumChannels> delayFeedbackVolume;
    juce::dsp::DryWetMixer<float> mixer;
};

