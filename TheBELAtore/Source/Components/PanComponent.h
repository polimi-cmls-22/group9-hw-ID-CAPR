/*
  ==============================================================================

    PanComponent.h
    Created: 30 May 2022 5:54:48pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Groups/PanGroup.h"
#include "Components.h"
//==============================================================================
/*
*/
class PanComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    PanComponent(AudioProcessorEditor& editor, 
        const PanGroup& state);
    ~PanComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInPanRange(float oscValue) { return (((oscValue - 55.0) * (1.0 - (-1.0))) / (545.0 - 55.0)) + (-1.0); };
private:
    AttachedSlider pannerSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanComponent)
};
