# MM-control-01
MMU 3-axis stepper control

## Latest stable versions & link to **RELEASES** for Precompiled HEX files

**MMU: V#: 2.1.5 RC	B#:  258**

**MK3: V#: 5.0.4 RC	B#: 2325**

**https://github.com/TheZeroBeast/MM-control-01/releases**

# POINTS OF NOTE

## POWER PANIC - IDLE FSensor Testing - BOWDEN CAL SETUP MENU - ACTION COMMANDS

* You **DO NOT** have to reset to factory settings, all the same EEPROM data structures are used as STOCK-PRUSA-FW.
* Bowden Length is still important as load is optimised to minimise the posibility of grinding in the event of the  
  MK3-FSensor not triggering, rare if setup correct, dust/particles still build up over time.  
  **DEFAULT FACTORY BOWDEN LENGETH OF 350mm**
* Value will be off if previously adjusted in STOCK FW. Adjust **BOWDEN_LENGTH** in **SETUP** menu,  
  this is to be just appearing at end of detatched BOWDEN tube (**NOTE ONLY F1 IS CALIBRATED**)
    1. Enter **SETUP** menu @ boot or using **MIDDLE** button while on **SERVICE** location with selector.
    2. As per STOCK FW, use **LEFT** button to move LED to fourth position.
    3. Use **MIDDLE** to send **Filament 1** in and out until satisfied of length.
    4. Use **LEFT** button to save and exit (**ONLY WHEN FILAMENT RETRACTED**)
* Distance to BONDTECH is set for factory R3 extruder configuration.
  1. Adjust type values with array on **line 20 in file MOTION.CPP** if custom value desired.
* Ensure filament sensor is enalbed via MK3 menu the first time you flash your MK3 to ensure your MMU2 gets messages when filament gets to the MK3.
* Blade isn't being used and can be removed. It has been known to add resistance to selector.
* Load/Unload and MMU Parameters should be set in Slic3r to minimise **GRINDING**  
  as depicted in images bellow from respective areas in Slic3r.
* **POWER PANIC** is now operational and will allow autorecover/continue when SD Printing
* Two action commands setup to be used with octoprint. "action: m600" & "action: mmuAttention" These can be setup with plugin Action Commands.
* Bowden limit raised to ~2.8m

## When in error state Active Extruder & or Previous Extruder LED/s will blink

###   RED and GREEEN Idicate F.I.N.D.A. State @ Load Failure
* Troubleshoot issue, usually was due to being caught on an edge or ground section of filament
  * Note: Failed **LOAD** where filament is found partly in Extruder requires a burst of air to clean MK3-FSensor
* If printer has shut down heaters, click MK3 wheel before clearing MMU2 issue with middle button
* **ALWAYS** ensure filament pulled clear of selector.
* Push middle button to rehome and continue
  * If nothing happens, filament is in FINDA, check again
  * If load fails again, give MK3-FSensor another burst of air and try again

###   RED and GREEEN Idicate F.I.N.D.A. State pluss GREEN for next extruder @ Unload Failure
* Troubleshoot issue, usually was due to ground section of filament
  * Note: If fail on **UNLOAD** the LED will show on the next extruder instead of current
* If printer has shut down heaters, click MK3 wheel before clearing MMU2 issue with middle button
* **ALWAYS** ensure filament pulled clear of selector.
* Push middle button to rehome and continue
  * If nothing happens, filament is in FINDA, check again


## Slic3r Advance Settging for load/unload Speed
![MMU2-Slic3r-LoadUnload-Speeds](/MMU2-Slic3r-LoadUnload-Speeds.png)

## Slic3r Single Extruder MMU Parameters under Printer Settings
![MMU2-Slic3r-SingleExtruderMMUParameters](/MMU2-Slic3r-SingleExtruderMMUParameters.png)

## Examble Octoprint Serial Communications for a successful load using MK3-FSensor
![MMU2-OctoprintSerialLoadExample](/MMU2-OctoprintSerialLoadExample.png)

# Building this custom setup
This is configured to work directly with MK2.5/MK3 with matching printer FW at link below to load filament to ExtruderLaserFilamentSensor and unload to FINDA Sensor.

https://github.com/TheZeroBeast/Prusa-Firmware


## Table of contents

<!--ts-->
   * [Building](#building)
     * [Cmake](#cmake)
       * [Automatic, remote, using travis-ci](#automatic-remote-using-travis-ci)
       * [Automatic, local, using script and prepared tools package](#automatic-local-using-script-and-prepared-tools-package)
       * [Manually with installed tools](#manually-with-installed-tools)
     * [Arduino](#arduino)
     * [PlatformIO](#platformio)
   * [Flashing](#flashing)
   * [Building documentation](#building-documentation)

<!--te-->

## Building
### Cmake
#### Automatic, remote, using travis-ci

Create new github user, eg. your_user_name-your_repository_name-travis. This step is not mandatory, only recomended to limit access rights for travis to single repository. Grant this user access to your repository. Register this user on https://travis-ci.org/. Create API key for this user. In Github click on this user, settings, Developer settings, Personal access tokens, Generate new token, select public_repo, click on Generate token. Copy this token.
Login into https://travis-ci.org/ enable build of your repository, click on repository setting, add environment variable ACCESS_TOKEN. As value paste your token.

Each commit is build, but only for tagged commits MM-control-01.hex is attached to your release by travis.

#### Automatic, local, using script and prepared tools package
##### Linux

You need unzip and wget tools.

run ./build.sh

It downloads neccessary tools, extracts it to ../MM-build-env-\<version\>, creates ../MM-control-01-build folder, configures build scripts in it and builds it using ninja.

##### Windows

Download MM-build-env-Win64-<version>.zip from https://github.com/prusa3d/MM-build-env/releases. Unpack it. Run configure.bat. This opens cmake-gui with preconfigured tools paths. Select path where is your source code located, select where you wish to build - out of source build is recomended. Click on generate, select generator - Ninja, or \<Your favourite IDE\> - Ninja.

Run build.bat generated in your binary directory.

#### Manually with installed tools

You need cmake, avr-gcc, avr-libc and cmake supported build system (e.g. ninja) installed.

Out of source tree build is recommended, in case of Eclipse CDT project file generation is necceessary. If you don't want out of source tree build, you can skip this step.
~~~
cd ..
mkdir MM-control-01_cmake
cd MM-control-01_cmake
~~~
Generate build system - consult cmake --help for build systems generators and IDE project files supported on your platform.
~~~
cmake -G "build system generator" path_to_source
~~~
example 1 - build system only
~~~
cmake -G "Ninja" ../MM-control-01
~~~
example 2 - build system and project file for your IDE
~~~
cmake -G "Eclipse CDT4 - Ninja ../MM-control-01
~~~
Invoke build system you selected in previous step. Example:
~~~
ninja
~~~
file MM-control-01.hex is generated.

### Arduino
Recomended version is arduino 1.8.5.  
in MM-control-01 subfolder create file version.h  
use version.h.in as template, replace ${value} with numbers or strings according to comments in template file.  
create file dirty.h with content if you are building unmodified git commit
~~~
#define FW_LOCAL_CHANGES 0
~~~
or
~~~
#define FW_LOCAL_CHANGES 1
~~~
if you have uncommitted local changes.
#### Adding MMUv2 board
In Arduino IDE open File / Settings  
Set Additional boards manager URL to:  
https://raw.githubusercontent.com/prusa3d/Arduino_Boards/master/IDE_Board_Manager/package_prusa3d_index.json  
Open Tools / Board: / Boards manager...
Install Prusa Research AVR Boards by Prusa Research  
which contains only one board:  
Original Prusa i3 MK3 Multi Material 2.0

Select board Original Prusa i3 MK3 Multi Material 2.0

Bootloader binary is shipped with the board, source is located at https://github.com/prusa3d/caterina
#### Build
click verify to build
### PlatformIO
PlatformIO build is not supported by Prusa Research, please report any PlatformIO related issues at https://github.com/awigen/MM-control-01/issues

## Flashing
### Windows
#### Arduino
click Upload
#### Slic3er
Hex file needs to be edited to be recognized as for MMUv2 in case of Arduino build. This is done automatically in cmake build.

Add following line to the begining of MM-control-01.hex:
~~~
; device = mm-control
~~~
#### Avrdude
Board needs to be reset to bootloader. Bootloader has 5 seconds timeout and then returns to the application.

This can be accomplished manually by clicking reset button on MMU, or programmatically by opening and closing its virtual serial line at baudrate 1500.

Than flash it using following command, replace \<virtual serial port\> with CDC device created by MMU usually com\<nr.\> under Windows and /dev/ttyACM\<nr.\> under Linux. -b baud rate is don't care value, probably doesn't have to be specified at all, as there is no physical uart.
~~~
avrdude -v -p atmega32u4 -c avr109 -P <virtual serial port> -b 57600 -D -U flash:w:MM-control-01.ino.hex:i
~~~

### Linux
Same as Windows, but there is known issue with ModemManager:

If you have the modemmanager installed, you either need to deinstall it, or blacklist the Prusa Research USB devices:

~~~
/etc/udev/rules.d/99-mm.rules

# Original Prusa i3 MK3 Multi Material 2.0 upgrade
ATTRS{idVendor}=="2c99", ATTRS{idProduct}=="0003", ENV{ID_MM_DEVICE_IGNORE}="1"
ATTRS{idVendor}=="2c99", ATTRS{idProduct}=="0004", ENV{ID_MM_DEVICE_IGNORE}="1"

$ sudo udevadm control --reload-rules
~~~
A request has been sent to Ubuntu, Debian and ModemManager to blacklist the whole Prusa Research VID space.

https://bugs.launchpad.net/ubuntu/+source/modemmanager/+bug/1781975

https://bugs.debian.org/cgi-bin/pkgreport.cgi?dist=unstable;package=modemmanager

and reported to
https://lists.freedesktop.org/archives/modemmanager-devel/2018-July/006471.html

## Building documentation
Run doxygen in MM-control-01 folder.
Documentation is generated in Doc subfolder.
