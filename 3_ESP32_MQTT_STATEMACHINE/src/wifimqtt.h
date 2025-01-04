
#include <Arduino.h>
#include "globals.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"
#include <ArduinoJson.h>

// MQTT
String clientId = "ESP32XIAO-statemachine";
const char *mqtt_server = "15.22.99.23";
const char *mqtt_user = "pixeledi_mag_statemachine";
const char *mqtt_password = "und_mqtt_gerne";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      // for this example not necessary

      client.subscribe("statemachine/nodered/update");
      client.subscribe("office/light/on");
      client.subscribe("office/light/off");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "office/light/on")
  {
    Serial.println("MQTT ON");
    state = ON;
  }
  else if (String(topic) == "office/light/off")
  {
    Serial.println("MQTT OFF");
    state = OFF;
  }
  else if (String(topic) == "statemachine/nodered/update")
  {
    // Stream& input;

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, messageTemp);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    const char *room = doc["room"];               // "Living Room"
    const char *temperature = doc["temperature"]; // "22.5"
    const char *humidity = doc["humidity"];       // "60"

    mySensorData.room = room;
    mySensorData.temperature = temperature;
    mySensorData.humidity = humidity;

    state = SHOWSENSORDATA;
  }

}

void connectAP()
{

  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 30)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}
