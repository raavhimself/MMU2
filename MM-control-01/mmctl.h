// mmctl.h - multimaterial switcher control
#ifndef _MMCTL_H
#define _MMCTL_H

#include <inttypes.h>
#include "config.h"

// public variables:
extern bool isPrinting;
extern bool isHomed;
extern int8_t active_extruder;
extern int8_t previous_extruder;
extern bool isFilamentLoaded;
extern bool isIdlerParked;
extern bool homedOnUnload;
extern uint16_t trackToolChanges;

// functions:
bool toolChange(int new_extruder);
bool feed_filament(void);
void led_blink(int _no);


#endif //_MMCTL_H
