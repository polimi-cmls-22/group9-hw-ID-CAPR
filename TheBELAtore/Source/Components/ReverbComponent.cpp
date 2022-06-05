/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 30 May 2022 5:13:00pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(AudioProcessorEditor& editor,
    const ReverbGroup& state)
    : roomSizeSlider    (editor, state.roomSize),
      widthSlider       (editor, state.width),
      dampingSlider     (editor, state.damping),
      freezeSlider      (editor, state.freeze),
      lowpassSlider     (editor, state.lowpass),
      highpassSlider    (editor, state.highpass),
      mixSlider         (editor, state.mix)
{
    addAllAndMakeVisible(*this, roomSizeSlider, widthSlider, dampingSlider, freezeSlider,
        lowpassSlider, highpassSlider, freezeSlider, mixSlider);
}

ReverbComponent::~ReverbComponent()
{
}


void ReverbComponent::resized()
{
    performLayout(getLocalBounds(), roomSizeSlider, widthSlider, dampingSlider, freezeSlider, lowpassSlider, highpassSlider, freezeSlider, mixSlider);

}

void ReverbComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float mixValue = convertInMixRange(message[0].getFloat32());
        getMixSlider().setValue(mixValue * 100);
    }
}

float ReverbComponent::convertInMixRange(float oscValue)
{
    return (((oscValue - 55.0) * (1.0 - 0.0)) / (545.0 - 55.0)) + 0.0;
}
