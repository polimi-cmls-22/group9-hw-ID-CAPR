/*
  ==============================================================================

    DistortionProcessor.h
    Created: 23 May 2022 11:56:33am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
class DistortionProcessor : public ProcessorBase
{
public:
    DistortionProcessor();
    ~DistortionProcessor() {};
    virtual void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;
    const juce::String getName() const override { return "Distortion"; }
    void updateOscParameter(float oscParameter) override;
    void selectAmp(int ampIndex);
    void updateParameters(float lpfCutoff, float hpfCutoff, float distGain, float compGain, int cabinetIndex, float mix);

private:
    juce::dsp::ProcessorChain<juce::dsp::FirstOrderTPTFilter<float>,
        juce::dsp::FirstOrderTPTFilter<float>,
        juce::dsp::Gain<float>,
        juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>, juce::dsp::Convolution> distortionChain;

    juce::dsp::DryWetMixer<float> mixer;
    juce::HeapBlock<char> heapBlock;
    juce::dsp::AudioBlock<float> tempBlock;
    enum 
    {
        lpfIndex,
        hpfIndex,
        distortionGainIndex,
        waveshaperIndex,
        compensationGainIndex,
        cabinetIndex
    };
};
