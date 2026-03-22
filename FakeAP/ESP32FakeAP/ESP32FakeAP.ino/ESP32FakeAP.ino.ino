
#include <M5StickCPlus.h>

void setup() {

  //Start
  Serial.begin(115200);
  M5.begin();
  
  //Variable declaration
  char greeting[] = "M5Stick Capitve Portal AP";
  char instrucHome[] = "Press Home To Start";

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

}

void loop() {
 
 //Start program if start button pressed
 if (M5.BtnA.wasPressed())
  {
  
  }
 }

