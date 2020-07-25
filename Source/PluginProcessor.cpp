/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EngrSaturationAudioProcessor::EngrSaturationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    mAPVTS.state.addListener(this);
    mAPVTS.state = ValueTree("savedParams");
}

EngrSaturationAudioProcessor::~EngrSaturationAudioProcessor()
{
}

//==============================================================================
const String EngrSaturationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EngrSaturationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EngrSaturationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EngrSaturationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EngrSaturationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EngrSaturationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EngrSaturationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EngrSaturationAudioProcessor::setCurrentProgram (int index)
{
}

const String EngrSaturationAudioProcessor::getProgramName (int index)
{
    return {};
}

void EngrSaturationAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EngrSaturationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;

    gain = Decibels::decibelsToGain(mAPVTS.getRawParameterValue("GAIN")->load());
    kp = mAPVTS.getRawParameterValue("KP")->load();
    ki = mAPVTS.getRawParameterValue("KI")->load();
    kd = mAPVTS.getRawParameterValue("KD")->load();
    mMaster = Decibels::decibelsToGain(mAPVTS.getRawParameterValue("MASTER")->load());
}

void EngrSaturationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EngrSaturationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EngrSaturationAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            in = channelData[sample] * gain;

            if (in < -0.2)
            {
                input = std::tanh(10.0f * (in + 0.2f)) / 10.0f - 0.2f;
            }
            else if (in > 0.8)
            {
                input = std::tanh(5.0f * (in - 0.8f)) / 5.0f + 0.8f;
            }
            else
            {
                input = in;
            }

            input = input / std::tanh(gain);
      
            error[channel] = error[channel] + ((input - state[channel]) + prevError[channel]) / 2 / sampleRate;
            derivative = (input - state[channel]) - prevError[channel];
            prevError[channel] = (input - state[channel]);
            
            state[channel] = kp * (input-state[channel]) + ki * error[channel] + kd * derivative;

            JUCE_SNAP_TO_ZERO(state[channel]);
            JUCE_SNAP_TO_ZERO(error[channel]); 
            JUCE_SNAP_TO_ZERO(derivative); 
            JUCE_SNAP_TO_ZERO(prevError[channel]);

            // Limiter protection
            if (limiterIsOn && Decibels::gainToDecibels(abs(state[channel]) * mMaster) > 0)
            {
                state[channel] = 0.0f;
                error[channel] = 0.0f;
                prevError[channel] = 0.0f;
                kp = 0;
                ki = 0;
                kd = 0;

            }

            channelData[sample] = state[channel] * mMaster;
        }
    }
}

//==============================================================================
bool EngrSaturationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EngrSaturationAudioProcessor::createEditor()
{
    return new EngrSaturationAudioProcessorEditor (*this);
}

//==============================================================================
void EngrSaturationAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this mehod to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xml(mAPVTS.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void EngrSaturationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> theParams(getXmlFromBinary(data, sizeInBytes));

    if (theParams != nullptr)
    {
        if (theParams->hasTagName(mAPVTS.state.getType()))
        {
            mAPVTS.state = ValueTree::fromXml(*theParams);
        }
    }
}

AudioProcessorValueTreeState::ParameterLayout EngrSaturationAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<AudioParameterFloat>("GAIN", "Gain", -60.0f, 30.0f, 0.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("KP", "Kp", 0.0f, 1.0f, 0.19f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("KI", "Ki", 0.0f, 40000.0f, 19500.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("KD", "Kd", 0.0f, 1.0f, 0.14f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("MASTER", "Master", -60.0f, 30.0f, 0.0f));

    return { parameters.begin(), parameters.end() };
}

void EngrSaturationAudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    gain = Decibels::decibelsToGain(mAPVTS.getRawParameterValue("GAIN")->load());
    kp = mAPVTS.getRawParameterValue("KP")->load();
    ki = mAPVTS.getRawParameterValue("KI")->load();
    kd = mAPVTS.getRawParameterValue("KD")->load();
    mMaster = Decibels::decibelsToGain(mAPVTS.getRawParameterValue("MASTER")->load());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EngrSaturationAudioProcessor();
}
