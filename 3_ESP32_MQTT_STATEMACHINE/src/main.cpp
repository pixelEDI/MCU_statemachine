/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://links.pixeledi.eu
Statemachine in Arduino Projekten 11.2024

*/

#include <Arduino.h>

#include "button.h"
#include "globals.h"
#include "wifimqtt.h"
#include "oled.h"

Button btn1(4);
Button btn2(5);

const byte ledPin = D10;

void checkButtons() {
  switch (btn1.checkBTN()) {
  case 1:
    state = ON;
    break;
  case 2:
    state = OFF;
    break;
  }

  switch (btn2.checkBTN()) {
  case 1:
    state = SENDMQTT;
    break;
  case 2:
    state = REQUESTVIAMQTT;
    break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  initOled();

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  state = WAIT;
}

void loop() {
  checkButtons();

  unsigned long currentMillis = millis();

  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32XIAO-statemachine");

  switch (state) {
  case ON:
    digitalWrite(ledPin, HIGH);
    Serial.println("ON");
    delay(1000);
    state = WAIT;
    break;
  case OFF:
    Serial.println("OFF");
    digitalWrite(ledPin, LOW);
    delay(1000);
    state = WAIT;
    break;
  case WAIT:
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      Serial.println("WAITING");
    }
    break;
  case SHOWSENSORDATA:
    Serial.println("SHOWSENSORDATA");
    showSensorValuesOnOled();
    delay(1000);
    state = WAIT;
    break;
  case SENDMQTT:
    Serial.println("SENDMQTT");
    client.publish("statemachine/esp32/update", "pixeledi_abonniert?");
    delay(1000);
    state = WAIT;
  case REQUESTVIAMQTT:
    Serial.println("REQUESTVIAMQTT");
    break;
  }
}
