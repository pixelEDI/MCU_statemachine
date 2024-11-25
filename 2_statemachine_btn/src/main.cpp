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

/*
  Enums definieren benannte Konstanten, die
  für bestimmte Werte stehen. In State Machines
  verwenden wir Enums, um die verschiedenen Zustände des MCUs
  klar und lesbar zu beschreiben.

   Vorteile:
     * Lesbarkeit: Anstatt numerische Werte (z.B. 1, 2, 3)
       nutzen wir benannte Konstanten (z.B. IDLE, RUNNING, PAUSED).
     * Klarheit: Der Code ist sofort verständlicher, da die
       Namen der Zustände deutlich machen, was jeder Zustand bedeutet.
     * Wartung: Änderungen an den Zuständen sind einfacher durchzuführen,
       da wir nur die Namen im Enum ändern müssen.
*/

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
    state = SINGLE_BLINK;
    break;
  case 2:
    state = LONG_BLINK;
    break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  state = OFF;
}

void loop() {

  checkButtons();

  switch (state) {
  case ON:
    digitalWrite(ledPin, HIGH);
    Serial.println("on");
    break;
  case SINGLE_BLINK:
    Serial.println("SINGLE_BLINK");
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
    }
    state = OFF;
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
    break;
  }
}
