Mechwarrior 5 only has relative position joystick input.  This program takes a joystick input
and and translates it to mouse input to provide absolute position input.  It's not completely
accurate, so it also presses the 'C' key to recentre when you centre the stick.

You will need to change your joystick config in the game to ensure that joystick is no longer
used for turning. (e.g. set the axis to one that doesn't exist).
You only want mouse input to be used for turning.

Usage: run the program to begin.  Close the window or hit ctrl-C to end.  It's a command line program
so there's no user interface.

To change the settings, supply them on the command line, or create a shortcut and put them
in the shortcut properties.

    --frame_rate 60.000000 [number of events to send per second]
    --scale_x 0.05500  [decrease if movement hits limits at left/right extremes]
    --scale_y 0.01700   [decrease if movement hits limits at top/bottom extremes]
    --disable_centre_key [whether to press key when joystick centred]
    --enable_centre_key                                 (1)
    --centre_key C       [key to press when joystick centred]
    --speed_limit_x 30   [max pixels to turn per frame, dont exceed game's limit]
    --speed_limit_y 10   [max pixels to turn per frame, dont exceed game's limit]
    --joystick_number 0  [joystick to use, see list above]
    --axis_number_x 0    [which axis is x]
    --axis_number_y 1    [which axis is y]
    --deadzone_x 2000    [joystick deadzone horizontal]
    --deadzone_y 2000    [joystick deadzone vertical]

Default settings work for me, but you might need to change scale_x and scale_y for different
mechs.  You want them high enough that you can twist all the way, but if they are any higher
then input will drift any time you hit the edges.

The game also has a maximum speed at which you can twist, if you increase the setting here
things will feel more responsive, but if you set it too high then inputs will be missed and
input will drift.

Centering temporarily resets drift,
so if you want to test just how bad drift is with current settings, then disable the centre key.

You shouldn't need to, but it may be necessary to run with administrator privileges.

TODO:
* different scales for left and right movement.
* investigate zooming