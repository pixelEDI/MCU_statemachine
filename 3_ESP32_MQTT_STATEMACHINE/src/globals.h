#include <Arduino.h>
#ifndef GLOBALS_
#define GLOBALS_

unsigned long previousMillis = millis();

enum { ON, OFF, SHOWSENSORDATA, WAIT, SENDMQTT, REQUESTVIAMQTT } state;

// nur bsp
struct sensordata {
  String room;
  String temperature;
  String humidity;
};

sensordata mySensorData;

#endif
