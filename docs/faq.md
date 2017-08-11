
# FAQ

### Unreal editor is slow when it is not the active window

Go to Edit/Editor Preferences, select "All Settings" and type "CPU" in the sarch box. 
It should find the setting titled "Use Less CPU when in Background", and you want to uncheck this checkbox.

### Drone doesn't fly properly, it just goes crazy

This can be a machine performance issue, check your [hard drive performance](hard_drive.md).

### It is not finding my pixhawk hardware

Check your settings.json file for this line "SerialPort":"*,115200".  The asterix here means "find any 
serial port that looks like a Pixhawk device, but this doesn't always work for all types of pixhawk hardware.
So on Windows you can find the actual COM port using Device Manager, look under "Ports (COM & LPT), plug the 
device in and see what new COM port shows up.  Let's say you see a new port named "USB Serial Port (COM5)". 
Well, then change the SerialPort setting to this: "SerialPort":"COM5,115200".  

On Linux, the device can be found by running "ls /dev/serial/by-id" if you see a device name listed that looks
like this `usb-3D_Robotics_PX4_FMU_v2.x_0-if00` then you can use that name to connect, like this:
"SerialPort":"/dev/serial/by-id/usb-3D_Robotics_PX4_FMU_v2.x_0-if00".  Note this long name is actually a symbolic link to the real 
name, if you use "ls -l ..." you can find that symbolic link, it is usually something like "/dev/ttyACM0",
so this will also work "SerialPort":"/dev/ttyACM0,115200".  But that mapping is similar to windows, it is
automatically assigned and can change, whereas the long name will work even if the actual tty serial device
mapping changes.

### My mouse disappears

Yes, Unreal steals the mouse, and we don't draw one.  So to get your mouse back just use Alt+TAB to switch to a different window.

### Build is not working on VS 2017

Known working config is:
````
Windows 10 (Education) x64
VS2015 update 3 (x86) with VC++
Cmake 3.7 (x86)
````
Even though cmake 3.7 says it added support for VS 2017 folks are reporting build issues with that.

### WARN  [commander] Takeoff denied, disarm and re-try

This happens if you try and take off when  PX4 still has not computed the home position.  PX4 will report the home
position once it is happy with the GPS signal, and you will see these messages:

````
INFO  [commander] home: 47.6414680, -122.1401672, 119.99
INFO  [tone_alarm] home_set
````

Up until this point in time, however, the PX4 will reject takeoff commands.


### What do the colors mean in the Segmentation View ?

See [Camera Views](camera_views.md) for information on the camera views and how to change them.

### Unreal 4.15 doesn't look as good as 4.14

Unreal 4.15 added the ability for Foliage LOD dithering to be disabled on a case-by-case basis by unchecking the `Dithered LOD Transition` checkbox in the foliage materials. Note that all materials used on all LODs need to have the checkbox checked in order for dithered LOD transitions to work.  When checked the transition of generated foliage will be a lot smoother and will look better than 4.14.


### Can I use an xbox controller to fly?
Yes, see [xbox controller](xbox_controller.md) for details.

### When I tell the drone to do something it always lands

For example, you use DroneShell `moveToPosition -z -20 -x 50 -y 0` which it does, but when it gets to the target location the
drone starts to land.  This is the default behavior of PX4 when offboard mode completes.  To set the drone to hover instead
set this PX4 parameter:
````
param set COM_OBL_ACT 1
````

### Can I build a hexacopter with AirSim?

Definitely, see [how to build a hexacopter](hexacopter.md).