/*
  ==============================================================================

    NoiseProcessor.h
    Created: 1 Jun 2022 4:12:23pm
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"

class NoiseProcessor : public ProcessorBase,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    NoiseProcessor();
    ~NoiseProcessor() {};
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void updateParameters(float outGaindB);
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Noise"; };
    //===================================================================
    void oscMessageReceived(const juce::OSCMessage& message) override;
    void showConnectionErrorMessage(const juce::String& messageText);
    //=================================================================

private:
    juce::Random random;
    juce::dsp::Gain<float> noiseGain;
    juce::dsp::DryWetMixer<float> mixer;
    float dryWetValue{ 0.0f };
    float noiseDBValue{ -40.0f };

};