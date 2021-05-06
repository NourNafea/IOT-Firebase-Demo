#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#include "creds.h"

#define LED D3

void connectToWiFi(char const *ssid, char const *password);

void setup()
{
  Serial.begin(115200);
  connectToWiFi(SSID, PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(LED, OUTPUT);
}


void loop()
{

  digitalWrite(LED, HIGH);
  Firebase.setString("Led status", "ON");
  delay(1000);
  
  digitalWrite(LED, LOW);
  Firebase.setString("Led status", "OFF");
  delay(1000);

  if (Firebase.failed())
  {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void connectToWiFi(char const *ssid, char const *password)
{
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}
