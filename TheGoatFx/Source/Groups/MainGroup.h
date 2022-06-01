/*
  ==============================================================================

    MainGroup.h
    Created: 27 May 2022 11:02:31am
    Author:  claud

  ==============================================================================
*/
#include <JuceHeader.h>
#include "../Parameters.h"
using Parameter = juce::AudioProcessorValueTreeState::Parameter;
using namespace juce::dsp;
#pragma once
namespace ID
{
    #define PARAMETER_ID(str) constexpr const char* str { #str };
        PARAMETER_ID(inputGain)
        PARAMETER_ID(outputGain)
        PARAMETER_ID(mainProcessorSlot1)
        PARAMETER_ID(mainProcessorSlot2)
        PARAMETER_ID(mainBypassSlot1)
        PARAMETER_ID(mainBypassSlot2)
    #undef PARAMETER_ID
}

struct MainGroup : Parameters
{
    explicit MainGroup(juce::AudioProcessorParameterGroup& layout)
        : inputGain(addToLayout<Parameter>(layout,
            ID::inputGain,
            "Input",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)),
        outputGain(addToLayout<Parameter>(layout,
            ID::outputGain,
            "Output",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)), 
        processorSlot1(addToLayout<juce::AudioParameterChoice>(layout,
            ID::mainProcessorSlot1,
            "",
            juce::StringArray{ "Empty", "Distortion", "Filter",
            "Phaser", "Chorus", "Delay", "Reverb", "Pan" },
            0)),
        processorSlot2(addToLayout<juce::AudioParameterChoice>(layout,
            ID::mainProcessorSlot2,
            "",
            juce::StringArray{ "Empty", "Distortion", "Filter",
            "Phaser", "Chorus", "Delay", "Reverb", "Pan" },
            0)),
        bypassSlot1(addToLayout<juce::AudioParameterBool>(layout,
            ID::mainBypassSlot1,
            "Bypass",
            false,
            "")),
        bypassSlot2(addToLayout<juce::AudioParameterBool>(layout,
            ID::mainBypassSlot2,
            "Bypass",
            false,
            "")){}

    Parameter& inputGain;
    Parameter& outputGain;
    juce::AudioParameterChoice& processorSlot1;
    juce::AudioParameterChoice& processorSlot2;
    juce::AudioParameterBool& bypassSlot1;
    juce::AudioParameterBool& bypassSlot2;
};

