#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>


#define FIREBASE_HOST "XXXXXXXXXXXXXXXXXXX"         //Real Time Database Referance URL without https:// and / at end
#define FIREBASE_AUTH "XXXXXXXXXXXXXXXXXXX"         //Database Secret Token
#define WIFI_SSID "XXXXXXXXXXXXXX"                  
#define WIFI_PASSWORD "XXXXXXXXXX"

void setup() {
  Serial.begin(9600);  // Set the baud rate to match the Arduino Uno
  
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {

   if (Serial.available()>0){
    int data = Serial.read();
    Serial.println(data);
    Firebase.pushInt("data", data);
    if (Firebase.failed()) {
      Serial.print("Setting /data failed: ");
      Serial.println(Firebase.error());  
      return;
    }
   delay(1000);  
   }
}

