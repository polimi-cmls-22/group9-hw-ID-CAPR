/*
  ==============================================================================

    PhaserGroup.h
    Created: 27 May 2022 11:03:32am
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
        PARAMETER_ID(phaserRate)
        PARAMETER_ID(phaserDepth)
        PARAMETER_ID(phaserCentreFrequency)
        PARAMETER_ID(phaserFeedback)
        PARAMETER_ID(phaserMix)
#undef PARAMETER_ID
}

struct PhaserGroup : Parameters
{
    explicit PhaserGroup(juce::AudioProcessorParameterGroup& layout)
        : rate(addToLayout<Parameter>(layout,
            ID::phaserRate,
            "Rate",
            "Hz",
            juce::NormalisableRange<float>(0.05f, 20.0f, 0.0f, 0.25f),
            1.0f,
            valueToTextFunction,
            textToValueFunction)),
        depth(addToLayout<Parameter>(layout,
            ID::phaserDepth,
            "Depth",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        centreFrequency(addToLayout<Parameter>(layout,
            ID::phaserCentreFrequency,
            "Center",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 20000.0f, 0.0f, 0.25f),
            600.0f,
            valueToTextFunction,
            textToValueFunction)),
        feedback(addToLayout<Parameter>(layout,
            ID::phaserFeedback,
            "Feedback",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        mix(addToLayout<Parameter>(layout,
            ID::phaserMix,
            "Mix",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)) {}

    Parameter& rate;
    Parameter& depth;
    Parameter& centreFrequency;
    Parameter& feedback;
    Parameter& mix;
};