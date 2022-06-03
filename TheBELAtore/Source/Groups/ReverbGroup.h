/*
  ==============================================================================

    ReverbGroup.h
    Created: 27 May 2022 11:03:52am
    Author:  claud

  ==============================================================================
*/
#include <JuceHeader.h>
#include "../Parameters.h"
using Parameter = juce::AudioProcessorValueTreeState::Parameter;
#pragma once
namespace ID
{
#define PARAMETER_ID(str) constexpr const char* str { #str };
        PARAMETER_ID(reverbRoomSize)
        PARAMETER_ID(reverbWidth)
        PARAMETER_ID(reverbDamping)
        PARAMETER_ID(reverbLowpass)
        PARAMETER_ID(reverbHighpass)
        PARAMETER_ID(reverbFreezeMode)
        PARAMETER_ID(reverbMix)
#undef PARAMETER_ID
}
struct ReverbGroup : Parameters
{
    explicit ReverbGroup(juce::AudioProcessorParameterGroup& layout)
        :roomSize(addToLayout<Parameter>(layout,
            ID::reverbRoomSize,
            "Room",
            "",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        width(addToLayout<Parameter>(layout,
            ID::reverbWidth,
            "Width",
            "",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        damping(addToLayout<Parameter>(layout,
            ID::reverbDamping,
            "Damping",
            "",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        lowpass(addToLayout<Parameter>(layout,
            ID::reverbLowpass,
            "Low-pass",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            22000.0f,
            valueToTextFunction,
            textToValueFunction)),
        highpass(addToLayout<Parameter>(layout,
            ID::reverbHighpass,
            "High-pass",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            20.0f,
            valueToTextFunction,
            textToValueFunction)),
        mix(addToLayout<Parameter>(layout,
            ID::reverbMix,
            "Reverb Mix",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        freeze(addToLayout<Parameter>(layout,
            ID::reverbFreezeMode,
            "Freeze",
            "",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)) {}

    Parameter& roomSize;
    Parameter& width;
    Parameter& damping;
    Parameter& freeze;
    Parameter& lowpass;
    Parameter& highpass;
    Parameter& mix;
};