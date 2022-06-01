#pragma once
#include <JuceHeader.h>
struct Parameters
{
    // template functions
    template <typename Param>
    static void add(juce::AudioProcessorParameterGroup& group, std::unique_ptr<Param> param)
    {
        group.addChild(std::move(param));
    }

    template <typename Param>
    static void add(juce::AudioProcessorValueTreeState::ParameterLayout& group, std::unique_ptr<Param> param)
    {
        group.add(std::move(param));
    }

    template <typename Param, typename Group, typename... Ts>
    static Param& addToLayout(Group& layout, Ts&&... ts)
    {
        auto param = std::make_unique<Param>(std::forward<Ts>(ts)...);
        auto& ref = *param;
        add(layout, std::move(param));
        return ref;
    }

    static juce::String valueToTextFunction(float x) { return juce::String(x, 2); }
    static float textToValueFunction(const juce::String& str) { return str.getFloatValue(); }
};