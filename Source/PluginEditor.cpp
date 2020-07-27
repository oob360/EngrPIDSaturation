/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EngrSaturationAudioProcessorEditor::EngrSaturationAudioProcessorEditor (EngrSaturationAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    titleLabel.setText("Engineer's PID Saturation", juce::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::lightgreen);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    mGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mGainSlider.setValue(processor.mGain);
    addAndMakeVisible(mGainSlider);
    mGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "GAIN", mGainSlider);

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&mGainSlider, false);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    gainLabel.setJustificationType(juce::Justification::centred);

    mKpSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mKpSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mKpSlider.setValue(processor.kp);
    addAndMakeVisible(mKpSlider);
    mKpAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "KP", mKpSlider);

    addAndMakeVisible(kpLabel);
    kpLabel.setText("Kp", juce::dontSendNotification);
    kpLabel.attachToComponent(&mKpSlider, false);
    kpLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    kpLabel.setJustificationType(juce::Justification::centred);

    mKiSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mKiSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mKiSlider.setValue(processor.ki);
    addAndMakeVisible(mKiSlider);
    mKiAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "KI", mKiSlider);

    addAndMakeVisible(kiLabel);
    kiLabel.setText("Ki", juce::dontSendNotification);
    kiLabel.attachToComponent(&mKiSlider, false);
    kiLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    kiLabel.setJustificationType(juce::Justification::centred);

    mKdSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mKdSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mKdSlider.setValue(processor.kd);
    addAndMakeVisible(mKdSlider);
    mKdAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "KD", mKdSlider);

    addAndMakeVisible(kdLabel);
    kdLabel.setText("Kd", juce::dontSendNotification);
    kdLabel.attachToComponent(&mKdSlider, false);
    kdLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    kdLabel.setJustificationType(juce::Justification::centred);

    mMasterSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mMasterSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mMasterSlider.setValue(processor.mMaster);
    addAndMakeVisible(mMasterSlider);
    mMasterAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "MASTER", mMasterSlider);

    addAndMakeVisible(masterLabel);
    masterLabel.setText("Master Level", juce::dontSendNotification);
    masterLabel.attachToComponent(&mMasterSlider, false);
    masterLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    masterLabel.setJustificationType(juce::Justification::centred);

    resetButton.addListener(this);
    resetButton.setButtonText("Reset state");
    addAndMakeVisible(resetButton);

    limiterButton.addListener(this);
    limiterButton.setButtonText("Safety Limiter @0dB Off");
    addAndMakeVisible(limiterButton);

    setSize (500, 300);
}

EngrSaturationAudioProcessorEditor::~EngrSaturationAudioProcessorEditor()
{
}

//==============================================================================
void EngrSaturationAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void EngrSaturationAudioProcessorEditor::resized()
{
    titleLabel.setBounds(0, 10, getWidth(), 30);

    mGainSlider.setBounds(getWidth() / 5 * 0, getHeight() / 2 - 75, getWidth() / 5, getHeight() / 2);
    mKpSlider.setBounds(getWidth() / 5 * 1, getHeight() / 2 - 75, getWidth() / 5, getHeight() / 2);
    mKiSlider.setBounds(getWidth() / 5 * 2, getHeight() / 2 - 75, getWidth() / 5, getHeight() / 2);
    mKdSlider.setBounds(getWidth() / 5 * 3, getHeight() / 2 - 75, getWidth() / 5, getHeight() / 2);
    mMasterSlider.setBounds(getWidth() / 5 * 4, getHeight() / 2 - 75, getWidth() / 5, getHeight() / 2);

    resetButton.setBounds(getWidth() / 2 - 50, getHeight() - 50, 100, 50);
    limiterButton.setBounds(0, getHeight() - 50, 100, 50);
    limiterButton.changeWidthToFitText();
}

void EngrSaturationAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &resetButton)
    {
        processor.state[0] = 0.0f;
        processor.state[1] = 0.0f;
        processor.error[0] = 0.0f;
        processor.error[1] = 0.0f;
        processor.derivative = 0.0f;
        processor.prevError[0] = 0.0f;
        processor.prevError[1] = 0.0f;
    }
    else if (button == &limiterButton)
    {
        processor.limiterIsOn = !(button->getToggleState());
    }
}