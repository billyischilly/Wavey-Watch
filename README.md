# Wavey-Watch

Wavey Watch is a project to make use of the TTGO T-Watch 2020 by Lilygo (and potentially other programmable watches) as a platform for MIDI/OSC based music applications using its bluetooth and WIFI connectivity and range of sensors. It is particularly concerned with creating a tool for disabled musicians who may benefit from an affordable and customisable wearable controller that offers lots of options for musical expression. That's not to say that its not a super fun and interesting controller for non-disabled musicians also!

Eventually I would like to add the ability to use two (or more) controllers simultaneously for more advanced control and gesture recognition functionality.

Currently there are the following play modes in development, at various levels of completion!

Air-harp Mode

Uses the accelerometer to determine the position of the users arm and sends notes via MIDI based on its angle along the Y axis. Movement on the X axis sends pitch bend messages allowing for vibrato by shaking arm left to right. A ball on the screen shows where you are in relation to the next/previous note threshold. A vibration motor also emits a pulse when you cross over a note threshold for haptic feedback.

Vibrato Mode

Intended as a way of augmenting the expressive possibilities of existing electronic instruments so you can get Roli-like functionality out of any old MIDI keyboard. Does not send note on and note off messages but sends pitchbend on X axis for vibrato/bends and expression CC on the Y axis. A wavey line on screen provides a visual guide to the depth of your vibrato and expression.

Send All OSC

Sends all sensors on the watch as OSC. The default addresses for these are set for use with Wekinator, a machine learning tool which allows for gesture recognition and more advanced motion controls of music software in a similar way to the Mi:Mu Gloves.

Send All MIDI (Not implemented yet)

Sends all sensors on the watch as Unassigned MIDI CC messages so that you can determine the usage of the controls on the target software.

Read more about the TTGO T Watch 2020 here...
http://www.lilygo.cn/prod_view.aspx?TypeId=50036&Id=1290&FId=t3:50036:3

...and the repository for the TTGO Watch Library is here...
https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library
