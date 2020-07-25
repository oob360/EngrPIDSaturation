/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class EngrSaturationAudioProcessorEditor  : public AudioProcessorEditor,
                                          public Button::Listener
{
public:
    EngrSaturationAudioProcessorEditor (EngrSaturationAudioProcessor&);
    ~EngrSaturationAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

private:
    Label titleLabel;
    Label gainLabel;
    Label kpLabel;
    Label kiLabel;
    Label kdLabel;
    Label masterLabel;
    
    Slider mGainSlider;

    Slider mKpSlider;
    Slider mKiSlider;
    Slider mKdSlider;

    Slider mMasterSlider;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mGainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mKpAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mKiAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mKdAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mMasterAttachment;

    TextButton resetButton;
    ToggleButton limiterButton;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EngrSaturationAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EngrSaturationAudioProcessorEditor)
};
