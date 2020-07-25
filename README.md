# EngrPIDSaturation

vst3 of the plugin is in the home directory. It should work with any DAW, but the plugin was specifically tested on Reaper, cakewalk, and ableton.

An asymmetrical saturation based on a PID controller.
https://en.wikipedia.org/wiki/PID_controller

The controller coefficients (kp, ki, and kd) can be modified directly by the user, which means that the user has to be careful of instabilities (ie your speakers might blow up with different combinations of kp, ki, and kd). You have been warned, and I am not liable for any damage to your speaker. Read ahead for recommended practices.

## How to use the plugin

To help with exploration, I've included a toggleable limiter that, by default, limits output levels to a maximum of 0dB relative to the volume knob in your DAW to avoid noise explosions.

Once you find a sound you like, feel free to toggle off the limiter in order to access the full gain range of the master level slider.

The filter is finnicky since instabilities are a possibility. If the plugin stops sounding, I recommend first lowering the level of whatever knob you were using to zero. If that doesn't work, press the "reset state" button. Also, if you are concerned about instabilities, I recommend moving the knobs slowly.
