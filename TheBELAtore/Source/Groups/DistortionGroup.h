/*
  ==============================================================================

    DistortionGroup.h
    Created: 27 May 2022 11:03:02am
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
        PARAMETER_ID(distortionType)
        PARAMETER_ID(distortionLowpass)
        PARAMETER_ID(distortionHighpass)
        PARAMETER_ID(distortionInGain)
        PARAMETER_ID(distortionCompGain)
        PARAMETER_ID(distortionCabinet)
        PARAMETER_ID(distortionMix)
    #undef PARAMETER_ID
}

struct DistortionGroup : Parameters
{
    explicit DistortionGroup(juce::AudioProcessorParameterGroup& layout)
        : distGain(addToLayout<Parameter>(layout,
            ID::distortionInGain,
            "Gain",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)),
        lowpass(addToLayout<Parameter>(layout,
            ID::distortionLowpass,
            "Post Low-pass",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            22000.0f,
            valueToTextFunction,
            textToValueFunction)),
        highpass(addToLayout<Parameter>(layout,
            ID::distortionHighpass,
            "Pre High-pass",
            "Hz",
            juce::NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.25f),
            20.0f,
            valueToTextFunction,
            textToValueFunction)),
        compGain(addToLayout<Parameter>(layout,
            ID::distortionCompGain,
            "Compensat.",
            "dB",
            juce::NormalisableRange<float>(-40.0f, 40.0f),
            0.0f,
            valueToTextFunction,
            textToValueFunction)),
        mix(addToLayout<Parameter>(layout,
            ID::distortionMix,
            "Mix",
            "%",
            juce::NormalisableRange<float>(0.0f, 100.0f),
            100.0f,
            valueToTextFunction,
            textToValueFunction)),
        cabinet(addToLayout<juce::AudioParameterChoice>(layout,
            ID::distortionCabinet,
            "Cabinet",
            juce::StringArray{"Bugera V55 Infinium",
            "Fender Frontman 212",
            "Marshall 1960VB",
            "Orange Crush CR60C",
            "VOX AC15C1"},
            1)) {}

    Parameter& distGain;
    Parameter& lowpass;
    Parameter& highpass;
    Parameter& compGain;
    juce::AudioParameterChoice& cabinet;
    Parameter& mix;
};