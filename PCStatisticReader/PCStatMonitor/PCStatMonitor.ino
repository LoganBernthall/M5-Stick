/*
************************************************************
*By - Logan Bernthall 01/02/26
*PC Statistic Monitor
*This is used with a PowerShell script that gets system stats, parses to JSON,
creates a simple HTTP server.
*This sketch will sniff out the data with a GET request and display it on the M5Stick.
************************************************************
*/

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <cstring> 

//Pre-Reqs
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://192.168.1.50:5000/stats";

void stats()
{

}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(3);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("M5Stick PC Stats",
                    M5.Lcd.width() / 2,
                    M5.Lcd.height() / 2 + 20);

  //Check Creds
  if (strcmp(ssid, "YOUR_WIFI_NAME") == 0 ||
      strcmp(password, "YOUR_WIFI_PASSWORD") == 0)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("ERROR:");
    M5.Lcd.println("Set WiFi");
    M5.Lcd.println("credentials in");
    M5.Lcd.println("the sketch!");
    
    while (true)
    {
      M5.update();
    }
  }

  // Only runs if credentials are valid
  WiFi.begin(ssid, password);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Connecting...");
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasPressed())
  {
    M5.Lcd.fillScreen(BLACK);
    stats();
  }
}