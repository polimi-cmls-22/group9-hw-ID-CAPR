/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/Components.h"
#include "Components/ChorusComponent.h"
#include "Components/FilterComponent.h"
#include "Components/PanComponent.h"
#include "Components/ReverbComponent.h"
#include "Components/PhaserComponent.h"
#include "Components/MainComponent.h"
#include "Components/ChorusComponent.h"
#include "Components/DelayComponent.h"
#include "Components/DistortionComponent.h"


using namespace juce;
//==============================================================================
/**
*/
class TheBelatoreAudioProcessorEditor  : public juce::AudioProcessorEditor,
    private juce::OSCReceiver, 
    private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    explicit TheBelatoreAudioProcessorEditor(TheBelatoreAudioProcessor& p)
        : AudioProcessorEditor(&p), audioProcessor(p)
    {

        comboSlot1.setSelectedId(audioProcessor.indexTab + 1, dontSendNotification);

        // setting as disabled the choice of the other processor slot
        comboSlot1.onChange = [this]
        {
            audioProcessor.indexTab = comboSlot1.getSelectedId() - 1;
            for (auto i = 0; i < comboSlot2.getNumItems(); ++i)
            {
                if(comboSlot2.getItemId(i) != comboSlot1.getSelectedId() || i == 0)
                    comboSlot2.setItemEnabled(comboSlot2.getItemId(i), true);
            }
            comboSlot2.setItemEnabled(comboSlot1.getSelectedId(), false);
            updateVisibility();
        };

        comboSlot2.setSelectedId(audioProcessor.indexTab + 1, dontSendNotification);

        // setting as disabled the choice of the other processor slot
        comboSlot2.onChange = [this]
        {
            audioProcessor.indexTab = comboSlot2.getSelectedId() - 1;
            for (auto i = 0; i < comboSlot1.getNumItems(); ++i)
            {
                if (comboSlot1.getItemId(i) != comboSlot2.getSelectedId() || i == 0)
                    comboSlot1.setItemEnabled(comboSlot1.getItemId(i), true);
            }
            comboSlot1.setItemEnabled(comboSlot2.getSelectedId(), false);
            updateVisibility();
        };

        addAllAndMakeVisible(*this,
            comboSlot1,
            comboSlot2,
            bypassSlot1,
            bypassSlot2,
            mainComponent,
            distortionComponent1,
            distortionComponent2,
            filterComponent1,
            filterComponent2,
            chorusComponent1,
            chorusComponent2,
            phaserComponent1,
            phaserComponent2,
            delayComponent1,
            delayComponent2,
            reverbComponent1,
            reverbComponent2,
            panComponent1,
            panComponent2);

        updateVisibility();

        setSize(800, 665);
        setResizable(false, false);

        // specify here on which UDP port number to receive incoming OSC messages
        if (!juce::OSCReceiver::connect(9000))
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");
    }
//    TheGoatFxAudioProcessorEditor (TheGoatFxAudioProcessor&);
    ~TheBelatoreAudioProcessorEditor() override;


    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void updateVisibility();

    //==============================================================================
    void oscMessageReceived(const juce::OSCMessage& message) override {};
    void showConnectionErrorMessage(const juce::String& messageText);

private:
    juce::Image campo, logoCapr, legno;

    enum EffectsTabs
    {
        TabDistortion = 2,
        TabFilter = 3,
        TabPhaser = 4,
        TabChorus = 5,
        TabDelay = 6,
        TabReverb = 7,
        TabPan = 8
    };

    // setting dimensions of sliders, labels and combo boxes
    struct GetTrackInfo
    {
        Grid::TrackInfo operator() (AttachedCombo&)             const { return 120_px; }

        Grid::TrackInfo operator() (AttachedToggle&)            const { return 80_px; }

        Grid::TrackInfo operator() (AttachedSlider&)            const { return 1_fr; }
    };

        static constexpr auto   topSize  = 40,
                                bottomSize = 40,
                                midSize    = 40,
                                tabSize    = 155;

    TheBelatoreAudioProcessor& audioProcessor;

    std::array<bool, 8> isListeningComponent1{ false };
    std::array<bool, 8> isListeningComponent2{ false };

    MainComponent       mainComponent{ *this, audioProcessor.getParameterValues().main };
    DistortionComponent distortionComponent1{ *this, audioProcessor.getParameterValues().distortion };
    DistortionComponent distortionComponent2{ *this, audioProcessor.getParameterValues().distortion };
    ReverbComponent     reverbComponent1{ *this, audioProcessor.getParameterValues().reverb };
    ReverbComponent     reverbComponent2{ *this, audioProcessor.getParameterValues().reverb };
    FilterComponent     filterComponent1{ *this, audioProcessor.getParameterValues().filter };
    FilterComponent     filterComponent2{ *this, audioProcessor.getParameterValues().filter };
    ChorusComponent     chorusComponent1{ *this, audioProcessor.getParameterValues().chorus };
    ChorusComponent     chorusComponent2{ *this, audioProcessor.getParameterValues().chorus };
    DelayComponent      delayComponent1{ *this, audioProcessor.getParameterValues().delay };
    DelayComponent      delayComponent2{ *this, audioProcessor.getParameterValues().delay };
    PhaserComponent     phaserComponent1{ *this, audioProcessor.getParameterValues().phaser };
    PhaserComponent     phaserComponent2{ *this, audioProcessor.getParameterValues().phaser };
    PanComponent        panComponent1{ *this, audioProcessor.getParameterValues().pan };
    PanComponent        panComponent2{ *this, audioProcessor.getParameterValues().pan };

    AttachedCombo attachedCombo1{ *this, audioProcessor.getParameterValues().main.processorSlot1 };
    AttachedCombo attachedCombo2{ *this, audioProcessor.getParameterValues().main.processorSlot2 };

    juce::ComboBox& comboSlot1 = attachedCombo1.getComboBox();
    juce::ComboBox& comboSlot2 = attachedCombo2.getComboBox();

    AttachedToggle attachedBypass1{ *this, audioProcessor.getParameterValues().main.bypassSlot1 };
    AttachedToggle attachedBypass2{ *this, audioProcessor.getParameterValues().main.bypassSlot2 };

    juce::ToggleButton& bypassSlot1 = attachedBypass1.getButton();
    juce::ToggleButton& bypassSlot2 = attachedBypass2.getButton();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheBelatoreAudioProcessorEditor)
};
