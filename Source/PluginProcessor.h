/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EngrSaturationAudioProcessor  : public AudioProcessor,
                                    public ValueTree::Listener
{
public:
    //==============================================================================
    EngrSaturationAudioProcessor();
    ~EngrSaturationAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float mGain;
    float gain;
    float input;
    float in;
    float mMaster;

    float kp;
    float ki;
    float kd;

    std::vector<float> state{ {0.0f, 0.0f} };
    std::vector<float> error{ {0.0f, 0.0f} };
    float derivative{ 0.0f };
    std::vector<float> prevError{ {0.0f, 0.0f} };

    bool limiterIsOn{ true };

    AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }


private:
    float sampleRate;

    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();

    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EngrSaturationAudioProcessor)
};
