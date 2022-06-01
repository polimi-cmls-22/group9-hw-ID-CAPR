/*
  ==============================================================================

    ReverbComponent.h
    Created: 30 May 2022 5:13:00pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Components.h"
#include "../Groups/ReverbGroup.h"
//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    ReverbComponent(AudioProcessorEditor& editor,
        const ReverbGroup& state);
    ~ReverbComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;

    //===============================================================
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInMixRange(float oscValue);
    //=================================================================
    juce::Slider& getMixSlider() { return mixSlider.getSlider(); };

private:
    AttachedSlider roomSizeSlider;
    AttachedSlider widthSlider;
    AttachedSlider dampingSlider;
    AttachedSlider freezeSlider;
    AttachedSlider lowpassSlider;
    AttachedSlider highpassSlider;
    AttachedSlider mixSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
