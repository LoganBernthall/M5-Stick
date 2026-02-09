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

//Pre-Reqs
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://192.168.1.50:5000/stats";

void stats()
{
  while (true)
  {
    stats();    
    delay(5000); //Sleep 5 seconds
  }
}

void setup() {
    //Start
  Serial.begin(115200);
  M5.begin();

  //Variable declaration
  char greeting[] = "M5Stick PC Stats";
  char instrucHome[] = "Press Home To Start";
  int cx = M5.Lcd.width() / 2;
  int screenW = M5.Lcd.width();
  int screenH = M5.Lcd.height();
  int centerX = screenW / 2;
  int logoY = 40; //Change to move
  int logoX = (screenW / 2) + 50; //Change 50 to move right
  //Setting portrait landscape
  M5.Lcd.setRotation(3);
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);

  M5.Lcd.setTextDatum(MC_DATUM);   // Middle-center anchor
  M5.Lcd.drawString(greeting,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 20);
  M5.Lcd.setTextSize(1);
  M5.Lcd.drawString(instrucHome,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 40);

    M5.Lcd.println("Connecting...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    M5.Lcd.println("WiFi OK");
    delay(1000);

}

void loop() 
{
  M5.update();
  
  if (M5.BtnA.wasPressed())
  {
    M5.update();
    M5.Lcd.fillScreen(BLACK);
    stats();
  }
}
