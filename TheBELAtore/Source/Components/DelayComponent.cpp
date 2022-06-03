/*
  ==============================================================================

    DelayComponent.cpp
    Created: 31 May 2022 9:34:47am
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(AudioProcessorEditor& editor,
    const DelayGroup& state) 
    :   valueSlider(editor, state.value),
        smoothingSlider(editor, state.smoothing),
        lowpassSlider(editor, state.lowpass),
        feedbackSlider(editor, state.feedback),
        mixSlider(editor, state.mix)
{
    addAllAndMakeVisible(*this, valueSlider, smoothingSlider, lowpassSlider, feedbackSlider, mixSlider);
}

DelayComponent::~DelayComponent()
{
}


void DelayComponent::resized()
{
    performLayout(getLocalBounds(), valueSlider, smoothingSlider, lowpassSlider, feedbackSlider, mixSlider);
}

void DelayComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float mixValue = convertInMixRange(message[0].getFloat32());
        getMixSlider().setValue(mixValue * 100);
    }
}
