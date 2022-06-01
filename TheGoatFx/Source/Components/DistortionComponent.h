/*
  ==============================================================================

    DistortionComponent.h
    Created: 30 May 2022 5:12:04pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Components.h"
#include "../Groups/DistortionGroup.h"

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    DistortionComponent(AudioProcessorEditor& editor,
        const DistortionGroup& state);
    ~DistortionComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;
    void oscMessageReceived(const juce::OSCMessage& message) override;
    float convertInMixRange(float oscValue){ return (((oscValue - 55.0) * (1.0 - 0.0)) / (545.0 - 55.0)) + 0.0; };

    //=================================================================
    juce::Slider& getMixSlider() { return mixSlider.getSlider(); };
private:
    AttachedSlider lowpassSlider, highpassSlider, mixSlider, distGainSlider, compGainSlider;
    AttachedCombo cabinetCombo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
