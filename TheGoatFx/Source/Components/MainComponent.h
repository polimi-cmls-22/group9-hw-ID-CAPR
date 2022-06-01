/*
  ==============================================================================

    MainComponent.h
    Created: 30 May 2022 5:11:44pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Groups/MainGroup.h"
#include "Components.h"
//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    MainComponent(AudioProcessorEditor& editor, const MainGroup& state);
    ~MainComponent() override;

    void paint(juce::Graphics&) override {};
    void resized() override;

private:
    AttachedSlider inputGainSlider;
    AttachedSlider outputGainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
