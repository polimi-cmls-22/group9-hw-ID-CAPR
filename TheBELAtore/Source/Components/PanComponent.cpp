/*
  ==============================================================================

    PanComponent.cpp
    Created: 30 May 2022 5:54:48pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanComponent.h"

//==============================================================================
PanComponent::PanComponent(AudioProcessorEditor& editor,
    const PanGroup& state)
    : pannerSlider(editor, state.panner)
{
    addAllAndMakeVisible(*this, pannerSlider);
}

PanComponent::~PanComponent()
{
}


void PanComponent::resized()
{
    performLayout(getLocalBounds(), pannerSlider);
}


void PanComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float panValue = convertInPanRange(message[0].getFloat32());
        pannerSlider.getSlider().setValue(panValue * 100);
    }
}

