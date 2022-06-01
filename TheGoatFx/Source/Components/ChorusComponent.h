/*
  ==============================================================================

    ChorusComponent.h
    Created: 30 May 2022 5:12:19pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Groups/ChorusGroup.h"
#include "Components.h"
//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    ChorusComponent(AudioProcessorEditor& editor,
        const ChorusGroup& state);
    ~ChorusComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInMixRange(float oscValue) { return (((oscValue - 55.0) * (1.0 - 0.0)) / (545.0 - 55.0)) + 0.0; };
    //=================================================================
    juce::Slider& getMixSlider() { return mixSlider.getSlider(); };
private:
    AttachedSlider rateSlider;
    AttachedSlider depthSlider;
    AttachedSlider centreDelaySlider;
    AttachedSlider feedbackSlider;
    AttachedSlider mixSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
