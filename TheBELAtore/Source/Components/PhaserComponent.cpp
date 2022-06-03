/*
  ==============================================================================

    PhaserComponent.cpp
    Created: 30 May 2022 5:12:35pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PhaserComponent.h"

//==============================================================================

PhaserComponent::PhaserComponent(AudioProcessorEditor& editor, const PhaserGroup& state)
:   rateSlider(editor, state.rate),
    depthSlider(editor, state.depth),
    centreFrequencySlider(editor, state.centreFrequency),
    feedbackSlider(editor, state.feedback),
    mixSlider(editor, state.mix)
{
    addAllAndMakeVisible(*this, rateSlider, depthSlider, centreFrequencySlider, feedbackSlider, mixSlider);

}

PhaserComponent::~PhaserComponent()
{
}

void PhaserComponent::resized()
{
    performLayout(getLocalBounds(), rateSlider, depthSlider, centreFrequencySlider, feedbackSlider, mixSlider);

}

void PhaserComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())
    {
        float mixValue = convertInMixRange(message[0].getFloat32());
        getMixSlider().setValue(mixValue * 100);
    }
}

float PhaserComponent::convertInMixRange(float oscValue)
{
    return (((oscValue - 55.0) * (1.0 - 0.0)) / (545.0 - 55.0)) + 0.0;
}
