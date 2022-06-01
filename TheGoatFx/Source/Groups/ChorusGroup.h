/*
  ==============================================================================

    ChorusGroup.h
    Created: 27 May 2022 11:03:24am
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
        PARAMETER_ID(chorusRate)
        PARAMETER_ID(chorusDepth)
        PARAMETER_ID(chorusCentreDelay)
        PARAMETER_ID(chorusFeedback)
        PARAMETER_ID(chorusMix)
#undef PARAMETER_ID
}

struct ChorusGroup : Parameters
{
    explicit ChorusGroup(juce::AudioProcessorParameterGroup& layout)
        : rate(addToLayout<Parameter>(layout,
            ID::chorusRate,
            "Rate",
            "Hz",
            juce::NormalisableRange<float>(0.05f, 20.0f, 0.0f, 0.25f),
            1.0f,
            valueToTextFunction,
            textToValueFunction)),
        depth(addToLayout<Parameter>(layout,
            ID::chorusDepth,
            "Depth",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        centreDelay(addToLayout<Parameter>(layout,
            ID::chorusCentreDelay,
            "Center",
            "ms",
            juce::NormalisableRange<float>(1.0f, 99.9f, 0.0f, 0.25f),
            7.0f,
            valueToTextFunction,
            textToValueFunction)),
        feedback(addToLayout<Parameter>(layout,
            ID::chorusFeedback,
            "Feedback",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        mix(addToLayout<Parameter>(layout,
            ID::chorusMix,
            "Mix",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)) {}

    Parameter& rate;
    Parameter& depth;
    Parameter& centreDelay;
    Parameter& feedback;
    Parameter& mix;
};