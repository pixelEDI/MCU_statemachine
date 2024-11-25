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

#include "globals.h"

const int ledPin = D10;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  state = OFF;
}

void loop() {

  switch (state) {
  case ON:
    Serial.println("ON");
    digitalWrite(ledPin, HIGH);
    delay(2000);
    state = SINGLE_BLINK;
    break;
  case SINGLE_BLINK:
    Serial.println("SINGLE_BLINK");
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
    }
    state = LONG_BLINK;
    break;
  case LONG_BLINK:

    Serial.println("LONG_BLINK");
    for (int i = 0; i < 3; i++) {

      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
    state = OFF;
    break;
  case OFF:
    Serial.println("OFF");
    digitalWrite(ledPin, LOW);
    delay(2000);
    state = ON;
    break;
  }
}
