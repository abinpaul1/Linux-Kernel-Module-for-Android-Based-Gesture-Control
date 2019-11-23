# Linux Kernel Driver For Voice and Button Control Using Android App 

Linux kernel driver to enable basic controls of operating system (Lock, Unlock, Brightness Control, Volume Control, Playback Control) using input recieved from an Android Device(app).
This repository contains code for the kernel driver and also the project files for the companion app for android phones.

## Getting Started

These drivers were tested for Ubuntu 18.04 and kernel versions 4.15.0-66-generic.

### Prerequisites

```
Android Studio

figlet
android-tools-adb
android-adb
linux-headers
build-essentials
```

### Running

- Compile, build and install the app on your phone. Ensure adb is set up between your machine and phone.
- Run make
- ./install.sh
- Now the client should be started and recieving input from the app


## How It Works - Basic Documentation 

We initialize a structure for an input device provided by kernel library
linux/input.h . We initialize a variable for a platform device, which when
registered by another function will provide a virtual file system through
which we can pass data to it.
All key events are reported using input_report_key function. These are
done by decoding the string that we write to the device file. Each events is
encoded to an ASCII character. Some of them include encoding
VOLUME_APP as ‘V’--ascii value 86 and VOLUME_DOWN as ‘v’--
ascii value 118, LOCK as L etc.
The function that decodes this is the sysfs write method. It is attached to
the attribute group via the DEVICE_ATTR function.
The function responsible for initialization of device driver is gesture_init
which will register itself as a gesture relaying platform. A sysfs node is
created to get data from user area space . Memory is allocated to the input
data device data structure. We set bits that tells the driver that the data it
gets are key events.

We also describe the exit function (gesture_uninit) to clean up the
registered devices and group, and that completes our kernel module.
Once this kernel module is loaded, a file will be exposed at
/sys/devices/platform/gesture/gevent to which we can pass our input
character corresponding to output from mobile app and the kernel will
execute accordingly.
A user level program shortcut.c is used to write input from the app to the
shared virtual file ‘gevent’ from which the kernel module reads user input.
The android app relays the output to the linux OS via the logcat part of adb
tool for debugging android. The app user interface consists of buttons to
increase/decrease brightness, increase/decrease volume, lock and unlock
the operating system.
It also offers a choice for passing input through voice control. The app
converts the spoken words to text and carries out the corresponding
operations.
