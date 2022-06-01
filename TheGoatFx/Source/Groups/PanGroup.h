/*
  ==============================================================================

    PanGroup.h
    Created: 27 May 2022 11:04:54am
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
    PARAMETER_ID(pan)
#undef PARAMETER_ID
}

struct PanGroup : Parameters
{
    explicit PanGroup(juce::AudioProcessorParameterGroup& layout)
        :panner(addToLayout<Parameter>(layout,
            ID::pan,
            "Panning",
            "",
            juce::NormalisableRange<float>(-100.0f, 100.0f),
            0.0f,
            valueToTextPanFunction,
            textToValuePanFunction)) {}

    //utility functions
    static juce::String getPanningTextForValue(float value)
    {
        if (value == 0.5f)
            return "center";

        if (value < 0.5f)
            return juce::String(juce::roundToInt((0.5f - value) * 200.0f)) + "%L";

        return juce::String(juce::roundToInt((value - 0.5f) * 200.0f)) + "%R";
    }

    static float getPanningValueForText(juce::String strText)
    {
        if (strText.compareIgnoreCase("center") == 0 || strText.compareIgnoreCase("c") == 0)
            return 0.5f;

        strText = strText.trim();

        if (strText.indexOfIgnoreCase("%L") != -1)
        {
            auto percentage = (float)strText.substring(0, strText.indexOf("%")).getDoubleValue();
            return (100.0f - percentage) / 100.0f * 0.5f;
        }

        if (strText.indexOfIgnoreCase("%R") != -1)
        {
            auto percentage = (float)strText.substring(0, strText.indexOf("%")).getDoubleValue();
            return percentage / 100.0f * 0.5f + 0.5f;
        }

        return 0.5f;
    }

    static juce::String valueToTextPanFunction(float x) { return getPanningTextForValue((x + 100.0f) / 200.0f); }
    static float textToValuePanFunction(const juce::String& str) { return getPanningValueForText(str) * 200.0f - 100.0f; }

    Parameter& panner;
};