# Build steps

for instruction on building this package and other packages from the Rotary Wing sub-group please follow this [link](https://docs.google.com/document/d/1Rl-851g5cFPR0NZfVkKsHbdwR2bMzr6qcSP2C-OcEaY/edit?usp=sharing)

## Description

This node uses the SDL library to grab keypresses. To do so, it opens a window where input is received. This window needs to becurrently focused, otherwise this node will not receive any key presses. 

## Topics

~keydown and ~keyup (keyboard/Key)