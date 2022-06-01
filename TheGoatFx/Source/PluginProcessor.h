/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Processors/ChorusProcessor.h"
#include "Processors/NoiseProcessor.h"
#include "Processors/DelayProcessor.h"
#include "Processors/DistortionProcessor.h"
#include "Processors/FilterProcessor.h"
#include "Processors/PhaserProcessor.h"
#include "Processors/ReverbProcessor.h"
#include "Processors/InputProcessor.h"
#include "Processors/MasterProcessor.h"
#include "Processors/PanProcessor.h"
#include "ParameterReferences.h"
#include "Processors/ProcessorBase.h"
//==============================================================================
/**
*/
using namespace juce;
using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

class TheBelatoreAudioProcessor  : public juce::AudioProcessor,
    private ValueTree::Listener
{
public:
    //==============================================================================
    TheBelatoreAudioProcessor();
    ~TheBelatoreAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void update();
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    const ParameterReferences& getParameterValues() const noexcept { return parameters; }
    void valueTreePropertyChanged(ValueTree&, const Identifier&) override;
    int indexTab = 0;
private:

    //==============================================================================
    struct LayoutAndReferences
    {
        AudioProcessorValueTreeState::ParameterLayout layout;
        ParameterReferences references;
    };

    explicit TheBelatoreAudioProcessor(AudioProcessorValueTreeState::ParameterLayout layout)
        : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                          .withOutput("Output", juce::AudioChannelSet::stereo(), true)),

        mainProcessor(new juce::AudioProcessorGraph()),
        parameters(layout),
        apvts(*this, nullptr, "state", std::move(layout))
    {
        apvts.state.addListener(this);
    }

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;

    Node::Ptr audioInputNode;
    Node::Ptr noiseNode;
    Node::Ptr inputProcessorNode;
    Node::Ptr masterProcessorNode;
    Node::Ptr audioOutputNode;

    Node::Ptr slot1Node;
    Node::Ptr slot2Node;

    virtual void initialiseGraph();
    virtual void connectAudioNodes();
    virtual void updateGraph();

    AudioProcessorValueTreeState::ParameterLayout layout;

    ParameterReferences parameters;
    AudioProcessorValueTreeState apvts;
    std::atomic<bool> requiresUpdate{ true };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheBelatoreAudioProcessor)
};
