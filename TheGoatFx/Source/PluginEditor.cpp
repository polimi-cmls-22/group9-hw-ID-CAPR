/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

TheBelatoreAudioProcessorEditor::~TheBelatoreAudioProcessorEditor()
{
}

//==============================================================================
void TheBelatoreAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();

    auto rectTop = rect.removeFromTop(topSize);
    auto rectBottom = rect.removeFromBottom(bottomSize);

    auto rectEffects2 = rect.removeFromBottom(tabSize);
    auto rectChoice2 = rect.removeFromBottom(midSize);
    auto rectEffects1 = rect.removeFromBottom(tabSize);
    auto rectChoice1 = rect.removeFromBottom(midSize);
    auto rectMain = rect.removeFromBottom(tabSize);
    auto rectMainText = rect.removeFromBottom(midSize);

    g.setColour(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.fillRect(rect);

    g.setColour(getLookAndFeel().findColour(ResizableWindow::backgroundColourId).brighter(0.2f));
    g.fillRect(rectMain);

    g.setColour(getLookAndFeel().findColour(ResizableWindow::backgroundColourId).darker(0.4f));
    g.fillRect(rectTop);
    g.fillRect(rectBottom);
    g.fillRect(rectMainText);

    logoCapr = juce::ImageCache::getFromMemory(BinaryData::LOGO_Capr_png, BinaryData::LOGO_Capr_pngSize).rescaled(95,95);
    campo = juce::ImageCache::getFromMemory(BinaryData::Campo_jpg, BinaryData::Campo_jpgSize).rescaled(800,665);
    legno = juce::ImageCache::getFromMemory(BinaryData::Legno_jpg, BinaryData::Legno_jpgSize).rescaled(rectChoice1.getWidth(), rectChoice1.getHeight());;

    g.setOpacity(0.5f);
    g.drawImageAt(campo, 0, 0);
    g.setOpacity(1.0f);
    g.drawImageAt(logoCapr, 690, -10);

    g.setOpacity(0.9f);
    g.drawImageAt(legno, rectChoice1.getX(), rectChoice1.getY());
    g.drawImageAt(legno, rectChoice2.getX(), rectChoice2.getY());


    juce::Rectangle<float> border(0, 0, getWidth(), getHeight());
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(border, 6.0f, 3.0f);

    juce::Rectangle<float> choice1Border(0, rectChoice1.getY(), rectChoice1.getWidth(), rectChoice1.getHeight());
    juce::Rectangle<float> choice2Border(0, rectChoice2.getY(), rectChoice2.getWidth(), rectChoice2.getHeight());
    g.setColour(juce::Colours::burlywood);
    g.drawRoundedRectangle(choice1Border, 3.0f, 1.0f);
    g.drawRoundedRectangle(choice2Border, 3.0f, 1.0f);


    g.setFont(juce::Font("Bauhaus 93", 30.0f, juce::Font::bold));
    g.setColour(Colours::antiquewhite);
    g.drawFittedText("THE BELATORE", rectTop.reduced(10, 0), Justification::centred, 1);

    g.setFont(juce::Font("Arial Rounded MT Bold", 20.0f, juce::Font::bold));
    g.drawFittedText("MASTER CONTROLS", rectMainText.reduced(10, 0), Justification::centredLeft, 1);
    g.drawFittedText("EFFECT 1", rectChoice1.reduced(10, 0), Justification::centredLeft, 1);    
    g.drawFittedText("EFFECT 2", rectChoice2.reduced(10, 0), Justification::centredLeft, 1);

}

void TheBelatoreAudioProcessorEditor::resized()
{
    auto rect = getLocalBounds();

    auto rectTop = rect.removeFromTop(topSize);
    auto rectBottom = rect.removeFromBottom(bottomSize);

    auto rectEffects2 = rect.removeFromBottom(tabSize);
    auto rectChoice2 = rect.removeFromBottom(midSize);
    auto rectEffects1 = rect.removeFromBottom(tabSize);
    auto rectChoice1 = rect.removeFromBottom(midSize);
    auto rectMain = rect.removeFromBottom(tabSize);

    comboSlot1.setBounds(rectChoice1.withSizeKeepingCentre(200, 24));
    bypassSlot1.setBounds(rectChoice1.withTrimmedLeft(700));
    comboSlot2.setBounds(rectChoice2.withSizeKeepingCentre(200, 24));
    bypassSlot2.setBounds(rectChoice2.withTrimmedLeft(700));

    rect.reduce(80, 0);
    rectEffects1.reduce(20, 0);
    rectEffects2.reduce(20, 0);
    rectMain.reduce(20, 0);

    mainComponent.setBounds(rectMain);

    forEach([&](Component& comp) { comp.setBounds(rectEffects1); },
        distortionComponent1,
        filterComponent1,
        phaserComponent1,
        chorusComponent1,
        delayComponent1,
        reverbComponent1,
        panComponent1);

    forEach([&](Component& comp) { comp.setBounds(rectEffects2); },
        distortionComponent2,
        filterComponent2,
        phaserComponent2,
        chorusComponent2,
        delayComponent2,
        reverbComponent2,
        panComponent2);
}

void TheBelatoreAudioProcessorEditor::updateVisibility()
{
    const auto indexEffect1 = comboSlot1.getSelectedId();
    const auto indexEffect2 = comboSlot2.getSelectedId();

    const auto op1 = [&](const std::tuple<Component&, int>& tup)
    {

        Component& comp = std::get<0>(tup);
        const int tabIndex = std::get<1>(tup);
        comp.setVisible(tabIndex == indexEffect1);
        switch (indexEffect1)
        {
        case TabDistortion:
            if (isListeningComponent2[TabDistortion - 1])
                removeListener(&distortionComponent2);
            addListener(&distortionComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabDistortion - 1] = true;
            break;
        case TabFilter:
            if (isListeningComponent2[TabFilter - 1])
                removeListener(&filterComponent2);
            addListener(&filterComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabFilter - 1] = true;
            break;
        case TabPhaser:
            if (isListeningComponent2[TabPhaser - 1])
                removeListener(&phaserComponent2);
            addListener(&phaserComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabPhaser - 1] = true;
            break;
        case TabChorus:
            if (isListeningComponent2[TabChorus - 1])
                removeListener(&chorusComponent2);
            addListener(&chorusComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabChorus - 1] = true;
            break;
        case TabDelay:
            if (isListeningComponent2[TabDelay - 1])
                removeListener(&delayComponent2);
            addListener(&delayComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabDelay - 1] = true;
            break;
        case TabReverb:
            if (isListeningComponent2[TabReverb - 1])
                removeListener(&reverbComponent2);
            addListener(&reverbComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabReverb - 1] = true;
            break;
        case TabPan:
            if (isListeningComponent2[TabDistortion - 1])
                removeListener(&panComponent2);
            addListener(&panComponent1, "/coordinates/xCoordinate");
            isListeningComponent1[TabPan - 1] = true;
            break;
        }
    };

    forEach(op1,
        std::forward_as_tuple(distortionComponent1, TabDistortion),
        std::forward_as_tuple(filterComponent1, TabFilter),
        std::forward_as_tuple(phaserComponent1, TabPhaser),
        std::forward_as_tuple(chorusComponent1, TabChorus),
        std::forward_as_tuple(delayComponent1, TabDelay),
        std::forward_as_tuple(reverbComponent1, TabReverb),
        std::forward_as_tuple(panComponent1, TabPan));

    const auto op2 = [&](const std::tuple<Component&, int>& tup)
    {
        Component& comp = std::get<0>(tup);
        const int tabIndex = std::get<1>(tup);
        comp.setVisible(tabIndex == indexEffect2);
        switch (indexEffect2)
        {
        case TabDistortion:
            if (isListeningComponent1[TabDistortion - 1])
                removeListener(&distortionComponent1);
            addListener(&distortionComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabDistortion - 1] = true;
            break;
        case TabFilter:
            if (isListeningComponent1[TabFilter - 1])
                removeListener(&filterComponent1);
            addListener(&filterComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabFilter - 1] = true;
            break;
        case TabPhaser:
            if (isListeningComponent1[TabPhaser - 1])
                removeListener(&phaserComponent1);
            addListener(&phaserComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabPhaser - 1] = true;
            break;
        case TabChorus:
            if (isListeningComponent1[TabChorus - 1])
                removeListener(&chorusComponent1);
            addListener(&chorusComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabChorus - 1] = true;
            break;
        case TabDelay:
            if (isListeningComponent1[TabDelay - 1])
                removeListener(&delayComponent1);
            addListener(&delayComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabDelay - 1] = true;
            break;
        case TabReverb:
            if (isListeningComponent1[TabReverb - 1])
                removeListener(&reverbComponent1);
            addListener(&reverbComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabReverb - 1] = true;
            break; 
        case TabPan:
            if (isListeningComponent1[TabPan - 1])
                removeListener(&panComponent1);
            addListener(&panComponent2, "/coordinates/yCoordinate");
            isListeningComponent2[TabPan - 1] = true;
            break;
        }
    };

    forEach(op2,
        std::forward_as_tuple(distortionComponent2, TabDistortion),
        std::forward_as_tuple(filterComponent2, TabFilter),
        std::forward_as_tuple(phaserComponent2, TabPhaser),
        std::forward_as_tuple(chorusComponent2, TabChorus),
        std::forward_as_tuple(delayComponent2, TabDelay),
        std::forward_as_tuple(reverbComponent2, TabReverb),
        std::forward_as_tuple(panComponent2, TabPan));

}

//======================================================================================
//OSC

void TheBelatoreAudioProcessorEditor::showConnectionErrorMessage(const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}



