/*
  ==============================================================================

    MainComponent.cpp
    Created: 30 May 2022 5:11:44pm
    Author:  claud

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(AudioProcessorEditor& editor, const MainGroup& state)
    :inputGainSlider(editor, state.inputGain),
    outputGainSlider(editor, state.outputGain)
{
    addAllAndMakeVisible(*this, inputGainSlider, outputGainSlider);
}

MainComponent::~MainComponent()
{
}


void MainComponent::resized()
{
    performLayout(getLocalBounds(), inputGainSlider, outputGainSlider);
}
