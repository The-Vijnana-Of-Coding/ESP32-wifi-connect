#include <Arduino.h>

// external libs
#include <WiFi.h>

// local libs
#include <credentials.h>

// wifi connection attempt counter
byte wifiCount = 0;
const byte wifiCountLimit = 11;

//#####  Connect to wifi function  ######//
void wifiConnect() {
    if (WiFi.status() != WL_CONNECTED && wifiCount < wifiCountLimit) {
        Serial.print('.');
        wifiCount++;
        delay(250);
        wifiConnect();
    } else if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("Local IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("RRSI: ");
        Serial.println(WiFi.RSSI());
        wifiCount = 0;
        delay(200);
    }
}
//////////////////////////////////////////////////////////////////////////

//#####  main Setup  ######//
void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    wifiConnect();
}
//////////////////////////////////////////////////////////////////////////

//#####  main Loop  ######//
void loop() {
    // put your main code here, to run repeatedly:
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println();
        Serial.print("Reattempting connection to WiFi ..");
        delay(1000);
        wifiConnect();
    }
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////