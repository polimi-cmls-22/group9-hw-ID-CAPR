/*
  ==============================================================================

    NoiseProcessor.cpp
    Created: 1 Jun 2022 4:12:23pm
    Author:  claud

  ==============================================================================
*/

#include "NoiseProcessor.h"

NoiseProcessor::NoiseProcessor()
{
    // tell the component to listen for OSC messages matching this address:
    //Components on the x position
    if (!juce::OSCReceiver::connect(9001))
        showConnectionErrorMessage("Error: could not connect to UDP port 9001.");
    else
    {
        juce::OSCReceiver::addListener(this, "/hit");
        juce::OSCReceiver::addListener(this, "/boom");
    }
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
    noiseGain.setRampDurationSeconds(0.05);
}

void NoiseProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mixer.setWetMixProportion(dryWetValue);
    noiseGain.setGainDecibels(noiseDBValue);
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    noiseGain.prepare(spec);
    mixer.prepare(spec);
}

void NoiseProcessor::updateParameters(float outGaindB)
{
}

void NoiseProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    if (context.isBypassed)
        return;

    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    const auto numChannels = juce::jmax(totalNumInputChannels, totalNumOutputChannels);

    const auto& inputBlock = context.getInputBlock();
    const auto& outputBlock = context.getOutputBlock();
    const auto numSamples = inputBlock.getNumSamples();

    mixer.pushDrySamples(inputBlock);

    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* samplesIn = inputBlock.getChannelPointer(channel);
        auto* samplesOut = outputBlock.getChannelPointer(channel);

        for (auto sample = 0; sample < numSamples; ++sample)
        {
            auto input = samplesIn[sample];
            input += random.nextFloat();
            samplesOut[sample] = input;
        }
    }
    noiseGain.process(context);
    mixer.mixWetSamples(outputBlock);
}

void NoiseProcessor::reset()
{
    mixer.reset();
    noiseGain.reset();
}

//OSC messages: this will increase or remove the noise effect in the sound, depending on which message arrives
void NoiseProcessor::oscMessageReceived(const juce::OSCMessage& message)
{
    if (!message.isEmpty() && message.size() == 1)
    {
        if (message.getAddressPattern() == "/hit" && message[0].getString() == "hit")
        {
            dryWetValue += random.getSystemRandom().nextFloat();
            dryWetValue = dryWetValue <= 1.0 ? dryWetValue : 1.0;
            mixer.setWetMixProportion(dryWetValue);

            noiseDBValue += random.getSystemRandom().nextFloat() * 10.0f;
            noiseDBValue = noiseDBValue <= 0.0f ? noiseDBValue : 0.0f;
            noiseGain.setGainDecibels(noiseDBValue);

            DBG(message[0].getString() << "Value noise: " << noiseDBValue<<"Value wet: "<< dryWetValue);
        }
        if (message.getAddressPattern() == "/boom" && message[0].getString() == "boom")
        {
            dryWetValue = 0.0f;
            noiseDBValue = -40.0f;
            mixer.setWetMixProportion(dryWetValue);
            noiseGain.setGainDecibels(noiseDBValue);
            DBG(message[0].getString() << "Value noise: " << noiseDBValue << "Value wet: " << dryWetValue);
        }
    }
}

void NoiseProcessor::showConnectionErrorMessage(const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}
