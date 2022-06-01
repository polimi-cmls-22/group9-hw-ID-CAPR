/*
  ==============================================================================

    FilterGroup.h
    Created: 27 May 2022 11:03:15am
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"
using Parameter = juce::AudioProcessorValueTreeState::Parameter;
namespace ID
{
#define PARAMETER_ID(str) constexpr const char* str { #str };
    PARAMETER_ID(filterCutoff)
    PARAMETER_ID(filterLowGain)
    PARAMETER_ID(filterHighGain)
#undef PARAMETER_ID
}
struct FilterGroup : Parameters
{
    explicit FilterGroup(juce::AudioProcessorParameterGroup& layout)
        :freq(addToLayout<Parameter>(layout,
            ID::filterCutoff,
            "Sep. Freq.",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            2000.0f,
            valueToTextFunction,
            textToValueFunction)),
        lowGain(addToLayout<Parameter>(layout,
            ID::filterLowGain,
            "Low volume",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)),
        highGain(addToLayout<Parameter>(layout,
            ID::filterHighGain,
            "High volume",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)) {}

    Parameter& freq;
    Parameter& lowGain;
    Parameter& highGain;
};