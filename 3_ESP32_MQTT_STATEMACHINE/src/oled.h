#include <Arduino.h>

#include "globals.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello XIAO!"));
  display.display();
  delay(2000);
}

void showSensorValuesOnOled() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(mySensorData.room);
  display.setCursor(0, 20);
  display.print(mySensorData.temperature);
  display.display();
}