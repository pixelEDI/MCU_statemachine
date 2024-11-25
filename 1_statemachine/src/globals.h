#include <Arduino.h>
#ifndef GLOBALS_
#define GLOBALS_

unsigned long previousMillis = millis();

enum { ON, OFF, SINGLE_BLINK, LONG_BLINK } state;

// nur bsp
struct fahrplan {
  String station;
  String departure1;
  String departure2;
  String departure3;
};

fahrplan myFahrplan[1];

#endif
