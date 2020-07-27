# EngrPIDSaturation

vst3 of the plugin is in the home directory. It should work with any DAW, but the plugin was specifically tested on Reaper, cakewalk, and ableton. This plugin is not straightforward to use; I highly recommend reading the "how to use" section below.

An asymmetrical saturation based on a PID controller.
https://en.wikipedia.org/wiki/PID_controller

The controller coefficients (kp, ki, and kd) can be modified directly by the user, which means that the user has to be careful of instabilities (ie your speakers might blow up with different combinations of kp, ki, and kd). You have been warned, and I am not liable for any damage to your speaker. Read ahead for recommended practices.

## How to use the plugin

A reminder: The controller coefficients (kp, ki, and kd) can be modified directly by the user, which means that the user has to be careful of instabilities (ie your speakers might blow up with different combinations of kp, ki, and kd).

To help with exploration and prevent speaker blowout, I've included a toggleable limiter that, by default, limits output levels to a maximum of 0dB relative to the volume knob in your DAW to avoid noise explosions.

Once you find a sound you like, feel free to toggle off the limiter in order to access the full gain range of the master level slider.

A few rules of thumb to keep in mind while playing with the coefficients:
* Start with Kd to zero and find values of Kp and Ki that you like. Ki is always quite stable at any value for any Kp and Kd. Kp is generally stable if Kd is zero. 
* Non-zero values of Kd make the plugin much more unstable. As Kd increases, Kp becomes less stable.

If the plugin stops sounding, you've probably found an unstable combination of coefficients. Here's a list of things you can try to get the plugin sounding again in ranked order:
1. I recommend first setting Kd to zero, and decreasing the master level knob to -60, then back up. 
2. Try lowering the level of whatever knob you were using to zero, then slowly increase it. 
3. Press the "reset state" button. 
4. Also, if you are concerned about instabilities, I recommend moving the knobs slowly.
