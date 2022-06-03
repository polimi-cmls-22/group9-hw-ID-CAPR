/*
  ==============================================================================

    PhaserComponent.h
    Created: 30 May 2022 5:12:35pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Components.h"
#include "../Groups/PhaserGroup.h"
//==============================================================================
/*
*/
class PhaserComponent  : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    PhaserComponent(AudioProcessorEditor& editor,
        const PhaserGroup& state);
    ~PhaserComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;

    //===================================================================
    void oscMessageReceived(const juce::OSCMessage& message) override;

    float convertInMixRange(float oscValue);
    //=================================================================
    juce::Slider& getMixSlider() { return mixSlider.getSlider(); };

private:
    AttachedSlider rateSlider;
    AttachedSlider depthSlider;
    AttachedSlider centreFrequencySlider;
    AttachedSlider feedbackSlider;
    AttachedSlider mixSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserComponent)
};
