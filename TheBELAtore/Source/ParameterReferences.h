#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "Groups/MainGroup.h"
#include "Groups/DistortionGroup.h"
#include "Groups/FilterGroup.h"
#include "Groups/PhaserGroup.h"
#include "Groups/ChorusGroup.h"
#include "Groups/ReverbGroup.h"
#include "Groups/DelayGroup.h"
#include "Groups/PanGroup.h"

//Instances of the parameter groups
struct ParameterReferences : Parameters
{
    explicit ParameterReferences(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
        : main(addToLayout<juce::AudioProcessorParameterGroup>(layout, "main", "Main", "|")),
          distortion(addToLayout<juce::AudioProcessorParameterGroup>(layout, "distortion", "Distortion", "|")),
          delay(addToLayout<juce::AudioProcessorParameterGroup>(layout, "delay", "Delay", "|")),
          filter(addToLayout<juce::AudioProcessorParameterGroup>(layout, "filter", "Filter", "|")),
          phaser(addToLayout<juce::AudioProcessorParameterGroup>(layout, "phaser", "Phaser", "|")),
          chorus(addToLayout<juce::AudioProcessorParameterGroup>(layout, "chorus", "Chorus", "|")),
          pan(addToLayout<juce::AudioProcessorParameterGroup>(layout, "pan", "Pan", "|")),
          reverb(addToLayout<juce::AudioProcessorParameterGroup>(layout, "reverb", "Reverb", "|")) {}

    MainGroup main;
    FilterGroup filter;
    DistortionGroup distortion;
    DelayGroup delay;
    PhaserGroup phaser;
    ChorusGroup chorus;
    ReverbGroup reverb;
    PanGroup pan;
};