/*
  ==============================================================================

    ComponentWithParamMenu.h
    Created: 29 May 2022 9:38:37pm
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
//==============================================================================
/*
* Template functions and classes that define some attached components that are contained in the components of the GUI
*/

using namespace juce;
template <typename... Components>
void addAllAndMakeVisible(Component& target, Components&... children)
{
    forEach([&](Component& child) { target.addAndMakeVisible(child); }, children...);
}

class ComponentWithParamMenu  : public juce::Component
{
public:
    ComponentWithParamMenu(juce::AudioProcessorEditor& editorIn, juce::RangedAudioParameter& paramIn)
        :editor(editorIn), param(paramIn) {};
    ~ComponentWithParamMenu() override {};

    void paint(juce::Graphics&) override {};
    void resized() override {};

private:
    juce::AudioProcessorEditor& editor;
    juce::RangedAudioParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentWithParamMenu)
};

class AttachedSlider : public ComponentWithParamMenu
{
public:
    AttachedSlider(AudioProcessorEditor& editorIn, RangedAudioParameter& paramIn)
        : ComponentWithParamMenu(editorIn, paramIn),
        label("", paramIn.name),
        attachment(paramIn, slider)
    {
        slider.addMouseListener(this, true);
        LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);
        addAllAndMakeVisible(*this, slider, label);

        slider.setTextValueSuffix(" " + paramIn.label);

        label.attachToComponent(&slider, false);
        label.setJustificationType(Justification::centred);
   
    }

    void resized() override { slider.setBounds(getLocalBounds().reduced(0, 20)); }
    juce::Slider& getSlider() { return slider; };
private:
    Slider slider{ Slider::RotaryVerticalDrag, Slider::TextBoxBelow };
    Label label;
    SliderParameterAttachment attachment;
    CustomLookAndFeel customLookAndFeel;
};

class AttachedToggle : public ComponentWithParamMenu
{
public:
    AttachedToggle(AudioProcessorEditor& editorIn, RangedAudioParameter& paramIn)
        : ComponentWithParamMenu(editorIn, paramIn),
        toggle(paramIn.name),
        attachment(paramIn, toggle)
    {
        toggle.addMouseListener(this, true);
        addAndMakeVisible(toggle);
    }

    void resized() override { toggle.setBounds(getLocalBounds()); }
    ToggleButton& getButton() { return toggle; };
private:
    ToggleButton toggle;
    ButtonParameterAttachment attachment;
};

class AttachedCombo : public ComponentWithParamMenu
{
public:
    AttachedCombo(AudioProcessorEditor& editorIn, RangedAudioParameter& paramIn)
        : ComponentWithParamMenu(editorIn, paramIn),
        combo(paramIn),
        label("", paramIn.name),
        attachment(paramIn, combo)
    {
        combo.addMouseListener(this, true);

        addAllAndMakeVisible(*this, combo, label);

        label.attachToComponent(&combo, false);
        label.setJustificationType(Justification::centred);
    }

    juce::ComboBox& getComboBox() { return combo; }

    void resized() override
    {
        combo.setBounds(getLocalBounds().withSizeKeepingCentre(jmin(getWidth(), 150), 24));
    }

private:
    struct ComboWithItems : public ComboBox
    {
        explicit ComboWithItems(RangedAudioParameter& param)
        {
            // Adding the list here in the constructor means that the combo
            // is already populated when we construct the attachment below
            addItemList(dynamic_cast<AudioParameterChoice&> (param).choices, 1);
        }
    };
    ComboWithItems combo;
    Label label;
    ComboBoxParameterAttachment attachment;
};

template <typename... Components>
static void performLayout(const Rectangle<int>& bounds, Components&... components)
{
    Grid grid;
    using Track = Grid::TrackInfo;

    grid.autoColumns = Track(1_fr);
    grid.autoRows = Track(1_fr);
    grid.columnGap = Grid::Px(10);
    grid.rowGap = Grid::Px(0);
    grid.autoFlow = Grid::AutoFlow::column;

    grid.templateColumns = { GetTrackInfo{} (components)... };
    grid.items = { GridItem(components)... };

    grid.performLayout(bounds);
}

struct GetTrackInfo
{
    Grid::TrackInfo operator() (AttachedCombo&)             const { return 120_px; }

    Grid::TrackInfo operator() (AttachedToggle&)            const { return 80_px; }

    Grid::TrackInfo operator() (AttachedSlider&)            const { return 1_fr; }
};

template <typename Func, typename... Items>
constexpr void forEach(Func&& func, Items&&... items)
noexcept (noexcept (std::initializer_list<int> { (func(std::forward<Items>(items)), 0)... }))
{
    (void)std::initializer_list<int> { ((void)func(std::forward<Items>(items)), 0)... };
}


constexpr auto PORT = 7563;
class GenericComponent : public juce::Component,
    public juce::OSCReceiver,
    public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    virtual void paint(juce::Graphics&) override {};
    virtual void resized() override {};
    virtual void oscMessageReceived(const juce::OSCMessage& message) override {};

    void showConnectionErrorMessage(const juce::String& messageText) 
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Connection error",
            messageText,
            "OK");
    }
};