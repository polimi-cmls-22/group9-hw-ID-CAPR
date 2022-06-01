/*
  ==============================================================================

    DelayComponent.h
    Created: 31 May 2022 9:34:47am
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Groups/DelayGroup.h"
#include "Components.h"
//==============================================================================
/*
*/
class DelayComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    DelayComponent(AudioProcessorEditor& editor,
        const DelayGroup& state);
    ~DelayComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInMixRange(float oscValue) { return (((oscValue - 55.0) * (1.0 - 0.0)) / (545.0 - 55.0)) + 0.0; };
    //=================================================================
    juce::Slider& getMixSlider() { return mixSlider.getSlider(); };

private:
    AttachedSlider valueSlider;
    AttachedSlider smoothingSlider;
    AttachedSlider lowpassSlider;
    AttachedSlider feedbackSlider;
    AttachedSlider mixSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};
