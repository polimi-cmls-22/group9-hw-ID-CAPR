/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;

//==============================================================================
TheBelatoreAudioProcessor::TheBelatoreAudioProcessor()
     : TheBelatoreAudioProcessor(AudioProcessorValueTreeState::ParameterLayout{})
{}

TheBelatoreAudioProcessor::~TheBelatoreAudioProcessor()
{
}

//==============================================================================
const juce::String TheBelatoreAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheBelatoreAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheBelatoreAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheBelatoreAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheBelatoreAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheBelatoreAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheBelatoreAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheBelatoreAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheBelatoreAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheBelatoreAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TheBelatoreAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
        getMainBusNumOutputChannels(),
        sampleRate, samplesPerBlock);

    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);
    initialiseGraph();
}

void TheBelatoreAudioProcessor::releaseResources()
{
    mainProcessor->releaseResources();
}

bool TheBelatoreAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void TheBelatoreAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (jmax(getTotalNumInputChannels(), getTotalNumOutputChannels()) == 0)
        return;

    juce::ScopedNoDenormals noDenormals;
    if (requiresUpdate.load())
        update();

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mainProcessor->processBlock(buffer, midiMessages);
    updateGraph();
}

//==============================================================================
bool TheBelatoreAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TheBelatoreAudioProcessor::createEditor()
{
    //return new TheGoatFxAudioProcessorEditor (*this);
    return new TheBelatoreAudioProcessorEditor(*this);
}

//==============================================================================
void TheBelatoreAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TheBelatoreAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void TheBelatoreAudioProcessor::initialiseGraph()
{
    mainProcessor->clear();

    audioInputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioInputNode));
    inputProcessorNode = mainProcessor->addNode(std::make_unique<InputProcessor>());
    noiseNode = mainProcessor->addNode(std::make_unique<NoiseProcessor>());
    masterProcessorNode = mainProcessor->addNode(std::make_unique<MasterProcessor>());
    audioOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));

    connectAudioNodes();
}

void TheBelatoreAudioProcessor::updateGraph()
{
    bool hasChanged = false;

    auto& processorSlot1 = parameters.main.processorSlot1;
    auto& processorSlot2 = parameters.main.processorSlot2;
    auto& bypassSlot1 = parameters.main.bypassSlot1;
    auto& bypassSlot2 = parameters.main.bypassSlot2;



    juce::Array<juce::AudioParameterChoice*> choices{ &processorSlot1,
                                                      &processorSlot2};

    juce::Array<juce::AudioParameterBool*> bypasses{  &bypassSlot1,
                                                      &bypassSlot2};


    juce::ReferenceCountedArray<Node> slots;
    slots.add(slot1Node);
    slots.add(slot2Node);

    for (int i = 0; i < 2; ++i)
    {
        auto& choice = choices.getReference(i);
        auto  slot = slots.getUnchecked(i);
        //empty slot
        if (choice->getIndex() == 0)
        {
            if (slot != nullptr)
            {
                mainProcessor->removeNode(slot.get());
                slots.set(i, nullptr);
                hasChanged = true;
            }
        }
        //FX Choices
        else if (choice->getIndex() == 1)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Distortion")
                    continue;

                mainProcessor->removeNode(slot.get());
            }

            slots.set(i, mainProcessor->addNode(std::make_unique<DistortionProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 2)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Filter")
                    continue;

                mainProcessor->removeNode(slot.get());
            }

            slots.set(i, mainProcessor->addNode(std::make_unique<FilterProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 3)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Phaser")
                    continue;

                mainProcessor->removeNode(slot.get());
            }
            slots.set(i, mainProcessor->addNode(std::make_unique<PhaserProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 4)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Chorus")
                    continue;

                mainProcessor->removeNode(slot.get());
            }
            slots.set(i, mainProcessor->addNode(std::make_unique<ChorusProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 5)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Delay")
                    continue;

                mainProcessor->removeNode(slot.get());
            }

            slots.set(i, mainProcessor->addNode(std::make_unique<DelayProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 6)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Reverb")
                    continue;

                mainProcessor->removeNode(slot.get());
            }

            slots.set(i, mainProcessor->addNode(std::make_unique<ReverbProcessor>()));
            hasChanged = true;
        }
        else if (choice->getIndex() == 7)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Pan")
                    continue;

                mainProcessor->removeNode(slot.get());
            }
            slots.set(i, mainProcessor->addNode(std::make_unique<PanProcessor>()));
            hasChanged = true;
        }
    }
    //if the graph has changed, the graph is redefined from scratch
    if (hasChanged)
    {
        for (auto connection : mainProcessor->getConnections())    
            mainProcessor->removeConnection(connection);

        juce::ReferenceCountedArray<Node> activeSlots;

        for (auto slot : slots)
        {
            if (slot != nullptr)
            {
                activeSlots.add(slot);                            

                slot->getProcessor()->setPlayConfigDetails(getMainBusNumInputChannels(),
                    getMainBusNumOutputChannels(),
                    getSampleRate(), getBlockSize());
            }
        }

        if (activeSlots.isEmpty())                                  
        {
            connectAudioNodes();
        }
        else
        {
            for (int i = 0; i < activeSlots.size() - 1; ++i)       
            {
                for (int channel = 0; channel < getNumOutputChannels(); ++channel)
                    mainProcessor->addConnection({ { activeSlots.getUnchecked(i)->nodeID,      channel },
                                                   { activeSlots.getUnchecked(i + 1)->nodeID,  channel } });
            }

            for (int channel = 0; channel < getNumOutputChannels(); ++channel)
            {
                mainProcessor->addConnection({  { audioInputNode->nodeID,           channel },
                                                { inputProcessorNode->nodeID,       channel } });
                mainProcessor->addConnection({  { inputProcessorNode->nodeID,       channel },
                                                { noiseNode->nodeID,                channel } });
                mainProcessor->addConnection({  { noiseNode->nodeID,                channel },
                                                { activeSlots.getFirst()->nodeID,   channel } });
                mainProcessor->addConnection({  { activeSlots.getLast()->nodeID,    channel },
                                                { masterProcessorNode->nodeID,      channel } });
                mainProcessor->addConnection({  { masterProcessorNode->nodeID,      channel },
                                                { audioOutputNode->nodeID,           channel } });
            }
        }

        for (auto node : mainProcessor->getNodes())                
            node->getProcessor()->enableAllBuses();
    }

    for (int i = 0; i < 2; ++i)
    {
        auto  slot = slots.getUnchecked(i);
        auto& bypass = bypasses.getReference(i);

        if (slot != nullptr)
            slot->setBypassed(bypass->get());
    }

    slot1Node = slots.getUnchecked(0);
    slot2Node = slots.getUnchecked(1);
}

//function called whenever a parameter changes
void TheBelatoreAudioProcessor::update()
{
    dynamic_cast<InputProcessor*>(inputProcessorNode->getProcessor())->updateParameters(parameters.main.inputGain.get());
    dynamic_cast<MasterProcessor*>(masterProcessorNode->getProcessor())->updateParameters(parameters.main.outputGain.get());

    juce::ReferenceCountedArray<Node> slots;
    slots.add(slot1Node);
    slots.add(slot2Node);


    for (auto slot : slots)
    {
        if (slot != nullptr && slot == slot1Node)
        {
            if (slot->getProcessor()->getName() == "Distortion")
            {
                auto* distortionProc = dynamic_cast<DistortionProcessor*>(slot->getProcessor());
                auto lpfCutoff = parameters.distortion.lowpass.get();
                auto hpfCutoff = parameters.distortion.highpass.get();
                auto distGain = parameters.distortion.distGain.get();
                auto compGain = parameters.distortion.compGain.get();
                auto mix = parameters.distortion.mix.get() / 100.0f;
                auto cabinet = parameters.distortion.cabinet.getIndex();
                distortionProc->updateParameters(lpfCutoff, hpfCutoff, distGain, compGain, cabinet, mix);
            }

            else if (slot->getProcessor()->getName() == "Filter")
            {
                auto* filterProc = dynamic_cast<FilterProcessor*>(slot->getProcessor());
                const auto freq = parameters.filter.freq.get();
                const auto newLowGain = parameters.filter.lowGain.get();
                const auto newHighGain = parameters.filter.highGain.get();
                filterProc->updateParameters(freq, newLowGain, newHighGain);
            }

            else if (slot->getProcessor()->getName() == "Delay")
            {
                auto* delayProc = dynamic_cast<DelayProcessor*>(slot->getProcessor());
                const auto value = parameters.delay.value.get();

                const auto feedbackGain = juce::Decibels::decibelsToGain(parameters.delay.feedback.get(), -100.0f);

                auto smooth = parameters.delay.smoothing.get();
                auto lowpassCutoff = parameters.delay.lowpass.get();
                auto mix = parameters.delay.mix.get();
                delayProc->updateParameters(value, feedbackGain, smooth, lowpassCutoff, mix);
            }

            else if (slot->getProcessor()->getName() == "Phaser")
            {
                auto* phaserProc = dynamic_cast<PhaserProcessor*>(slot->getProcessor());
                auto rate = parameters.phaser.rate.get();
                auto depth = parameters.phaser.depth.get() / 100.0f;
                auto centreFrequency = parameters.phaser.centreFrequency.get();
                auto feedback = parameters.phaser.feedback.get() / 100.0f * 0.95f;
                auto mix = parameters.phaser.mix.get() / 100.0f;
                phaserProc->updateParameters(rate, depth, centreFrequency, feedback, mix);
            }

            else if (slot->getProcessor()->getName() == "Reverb")
            {
                auto* reverbProc = dynamic_cast<ReverbProcessor*>(slot->getProcessor());
                auto room = parameters.reverb.roomSize.get() / 100.0f;
                auto width = parameters.reverb.width.get() / 100.0f;
                auto damping = parameters.reverb.damping.get() / 100.0f;
                auto lpf = parameters.reverb.lowpass.get();
                auto hpf = parameters.reverb.highpass.get();
                auto freeze = parameters.reverb.freeze.get() / 100.0f;
                auto mix = parameters.reverb.mix.get() / 100.0f;
                reverbProc->updateParameters(room, width, damping, freeze, mix, lpf, hpf);
            }

            else if (slot->getProcessor()->getName() == "Chorus")
            {
                auto* chorusProc = dynamic_cast<ChorusProcessor*>(slot->getProcessor());
                auto rate = parameters.chorus.rate.get();
                auto depth = parameters.chorus.depth.get() / 100.0f;
                auto centreDelay = parameters.chorus.centreDelay.get();
                auto feedback = parameters.chorus.feedback.get() / 100.0f * 0.95f;
                auto mix = parameters.chorus.mix.get() / 100.0f;
                chorusProc->updateParameters(rate, depth, centreDelay, feedback, mix);
            }
            else if (slot->getProcessor()->getName() == "Pan")
            {
                auto* panProc = dynamic_cast<PanProcessor*>(slot->getProcessor());
                auto pan = parameters.pan.panner.get() / 100.0f;
                panProc->updateParameters(pan);
            }
        }
        else if (slot != nullptr && slot == slot2Node)
        {
            if (slot->getProcessor()->getName() == "Distortion")
            {
                auto* distortionProc = dynamic_cast<DistortionProcessor*>(slot->getProcessor());
                auto lpfCutoff = parameters.distortion.lowpass.get();
                auto hpfCutoff = parameters.distortion.highpass.get();
                auto distGain = parameters.distortion.distGain.get();
                auto compGain = parameters.distortion.compGain.get();
                auto mix = parameters.distortion.mix.get() / 100.0f;
                auto cabinet = parameters.distortion.cabinet.getIndex();
                distortionProc->updateParameters(lpfCutoff, hpfCutoff, distGain, compGain, cabinet, mix);
            }

            else if (slot->getProcessor()->getName() == "Filter")
            {
                auto* filterProc = dynamic_cast<FilterProcessor*>(slot->getProcessor());
                const auto freq = parameters.filter.freq.get();
                const auto newLowGain = parameters.filter.lowGain.get();
                const auto newHighGain = parameters.filter.highGain.get();
                filterProc->updateParameters(freq, newLowGain, newHighGain);
            }

            else if (slot->getProcessor()->getName() == "Delay")
            {
                auto* delayProc = dynamic_cast<DelayProcessor*>(slot->getProcessor());
                const auto value = parameters.delay.value.get();

                const auto feedbackGain = juce::Decibels::decibelsToGain(parameters.delay.feedback.get(), -100.0f);

                auto smooth = parameters.delay.smoothing.get();
                auto lowpassCutoff = parameters.delay.lowpass.get();
                auto mix = parameters.delay.mix.get();
                delayProc->updateParameters(value, feedbackGain, smooth, lowpassCutoff, mix);
            }

            else if (slot->getProcessor()->getName() == "Phaser")
            {
                auto* phaserProc = dynamic_cast<PhaserProcessor*>(slot->getProcessor());
                auto rate = parameters.phaser.rate.get();
                auto depth = parameters.phaser.depth.get() / 100.0f;
                auto centreFrequency = parameters.phaser.centreFrequency.get();
                auto feedback = parameters.phaser.feedback.get() / 100.0f * 0.95f;
                auto mix = parameters.phaser.mix.get() / 100.0f;
                phaserProc->updateParameters(rate, depth, centreFrequency, feedback, mix);
            }

            else if (slot->getProcessor()->getName() == "Reverb")
            {
                auto* reverbProc = dynamic_cast<ReverbProcessor*>(slot->getProcessor());
                auto room = parameters.reverb.roomSize.get() / 100.0f;
                auto width = parameters.reverb.width.get() / 100.0f;
                auto damping = parameters.reverb.damping.get() / 100.0f;
                auto lpf = parameters.reverb.lowpass.get();
                auto hpf = parameters.reverb.highpass.get();
                auto freeze = parameters.reverb.freeze.get() / 100.0f;
                auto mix = parameters.reverb.mix.get() / 100.0f;
                reverbProc->updateParameters(room, width, damping, freeze, mix, lpf, hpf);
            }

            else if (slot->getProcessor()->getName() == "Chorus")
            {
                auto* chorusProc = dynamic_cast<ChorusProcessor*>(slot->getProcessor());
                auto rate = parameters.chorus.rate.get();
                auto depth = parameters.chorus.depth.get() / 100.0f;
                auto centreDelay = parameters.chorus.centreDelay.get();
                auto feedback = parameters.chorus.feedback.get() / 100.0f * 0.95f;
                auto mix = parameters.chorus.mix.get() / 100.0f;
                chorusProc->updateParameters(rate, depth, centreDelay, feedback, mix);
            }
            else if (slot->getProcessor()->getName() == "Pan")
            {
                auto* panProc = dynamic_cast<PanProcessor*>(slot->getProcessor());
                auto pan = parameters.pan.panner.get() / 100.0f;
                panProc->updateParameters(pan);
            }
        }
    }
    requiresUpdate.store(false);
}

//standard connections when there are no effects in the slot
void TheBelatoreAudioProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < getNumOutputChannels(); ++channel)
    {
        mainProcessor->addConnection({ { audioInputNode->nodeID,  channel },
                            { inputProcessorNode->nodeID, channel } });
        mainProcessor->addConnection({ { inputProcessorNode->nodeID,  channel },
                            { noiseNode->nodeID, channel } });
        mainProcessor->addConnection({ { noiseNode->nodeID,  channel },
                            { masterProcessorNode->nodeID, channel } });
        mainProcessor->addConnection({ { masterProcessorNode->nodeID,  channel },
                            { audioOutputNode->nodeID, channel } });
    }
}

void TheBelatoreAudioProcessor::valueTreePropertyChanged(ValueTree&, const Identifier&)
{
    requiresUpdate.store(true);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheBelatoreAudioProcessor();
}
