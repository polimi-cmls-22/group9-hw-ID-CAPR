/*
  ==============================================================================

    FliterComponent.cpp
    Created: 30 May 2022 5:38:51pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(AudioProcessorEditor& editor,
    const FilterGroup& state)
    : frequencySlider(editor, state.freq),
      lowGainSlider(editor, state.lowGain),
      highGainSlider(editor, state.highGain)
{
    addAllAndMakeVisible(*this, frequencySlider, lowGainSlider, highGainSlider);
}


FilterComponent::~FilterComponent()
{
}


void FilterComponent::resized()
{
    performLayout(getLocalBounds(), frequencySlider, lowGainSlider, highGainSlider);
}

void FilterComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float frequencyValue = convertInFilterFrequencyRange(message[0].getFloat32());
        getFrequencySlider().setValue(frequencyValue);
    }
}
