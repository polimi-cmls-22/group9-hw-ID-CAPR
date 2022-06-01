/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 30 May 2022 5:12:19pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(AudioProcessorEditor& editor,
    const ChorusGroup& state)
    : rateSlider(editor, state.rate),
    depthSlider(editor, state.depth),
    centreDelaySlider(editor, state.centreDelay),
    feedbackSlider(editor, state.feedback),
    mixSlider(editor, state.mix)
{
    addAllAndMakeVisible(*this, rateSlider, depthSlider, centreDelaySlider, feedbackSlider, mixSlider);

}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::resized()
{
    performLayout(getLocalBounds(), rateSlider, depthSlider, centreDelaySlider, feedbackSlider, mixSlider);
}

void ChorusComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float mixValue = convertInMixRange(message[0].getFloat32());
        getMixSlider().setValue(mixValue * 100);
    }
}
