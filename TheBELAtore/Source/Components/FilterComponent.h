/*
  ==============================================================================

    FilterComponent.h
    Created: 30 May 2022 5:38:51pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Groups/FilterGroup.h"
#include "Components.h"
//==============================================================================
/*
*/
class FilterComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    FilterComponent(AudioProcessorEditor& editor,
        const FilterGroup& state);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override {};
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInFilterFrequencyRange(float oscValue) { return (((oscValue - 55.0) * (22000.0 - 20.0)) / (545.0 - 55.0)) + 20.0; };
    //===================================================================
    juce::Slider& getFrequencySlider() { return frequencySlider.getSlider(); };
private:
    AttachedSlider frequencySlider;
    AttachedSlider lowGainSlider;
    AttachedSlider highGainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
