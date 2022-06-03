/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 30 May 2022 5:12:04pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"
//==============================================================================
DistortionComponent::DistortionComponent(AudioProcessorEditor& editor,
    const DistortionGroup& state)
    : lowpassSlider(editor, state.lowpass),
    highpassSlider(editor, state.highpass),
    mixSlider(editor, state.mix),
    distGainSlider(editor, state.distGain),
    compGainSlider(editor, state.compGain),
    cabinetCombo(editor, state.cabinet)
{
    addAllAndMakeVisible(*this, lowpassSlider, highpassSlider, mixSlider, distGainSlider, compGainSlider, cabinetCombo);
}


DistortionComponent::~DistortionComponent()
{
}


void DistortionComponent::resized()
{
    performLayout(getLocalBounds(), distGainSlider, highpassSlider, lowpassSlider, compGainSlider, mixSlider, cabinetCombo);
}

void DistortionComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float mixValue = convertInMixRange(message[0].getFloat32());
        getMixSlider().setValue(mixValue * 100);
    }
}
