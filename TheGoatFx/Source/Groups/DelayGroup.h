/*
  ==============================================================================

    DelayGroup.h
    Created: 27 May 2022 11:04:40am
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
        PARAMETER_ID(delayType)
        PARAMETER_ID(delayValue)
        PARAMETER_ID(delaySmoothing)
        PARAMETER_ID(delayLowpass)
        PARAMETER_ID(delayFeedback)
        PARAMETER_ID(delayMix)
#undef PARAMETER_ID
}

struct DelayGroup : Parameters
{
    explicit DelayGroup(juce::AudioProcessorParameterGroup& layout)
        : type(addToLayout<juce::AudioParameterChoice>(layout,
            ID::delayType,
            "DL Type",
            juce::StringArray{ "None", "Linear", "Lagrange", "Thiran" },
            1)),
        value(addToLayout<Parameter>(layout,
            ID::delayValue,
            "Delay",
            "ms",
            juce::NormalisableRange<float>(0.01f, 2000.0f),
            100.0f,
            valueToTextFunction,
            textToValueFunction)),
        smoothing(addToLayout<Parameter>(layout,
            ID::delaySmoothing,
            "Smooth",
            "ms",
            juce::NormalisableRange<float>(20.0f, 10000.0f, 0.0f, 0.25f),
            400.0f,
            valueToTextFunction,
            textToValueFunction)),
        lowpass(addToLayout<Parameter>(layout,
            ID::delayLowpass,
            "Low-pass",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            22000.0f,
            valueToTextFunction,
            textToValueFunction)),
        mix(addToLayout<Parameter>(layout,
            ID::delayMix,
            "Delay Mix",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            50.0f,
            valueToTextFunction,
            textToValueFunction)),
        feedback(addToLayout<Parameter>(layout,
            ID::delayFeedback,
            "Feedback",
            "dB",
            juce::NormalisableRange<float>(-100.0f, 0.0f),
            -100.0f,
            valueToTextFunction,
            textToValueFunction)) {}

    juce::AudioParameterChoice& type;
    Parameter& value;
    Parameter& smoothing;
    Parameter& lowpass;
    Parameter& mix;
    Parameter& feedback;
};