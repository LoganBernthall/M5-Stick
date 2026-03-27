#include <M5StickCPlus.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(9);


void setup() {
  
  Serial.begin(115200);
  M5.begin();

    irsend.begin();
  
  //Variable declaration
  char intro[] = "M5Stick TVIRBlaster";
  char greeting[] = "Turn The TV OFF!";
  char instruct[] = "Press Button To Blast";

  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLUE);
  delay(500);
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setTextSize(2); 

  M5.Lcd.setTextDatum(MC_DATUM);   // Middle-center anchor
  M5.Lcd.drawString(intro,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 5);
  M5.Lcd.drawString(greeting,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 20);
  M5.Lcd.setTextSize(1); 
  M5.Lcd.drawString(instruct,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 35);
}

void loop() {
  //Blast IR codes to turn TV off
   if (M5.BtnA.wasPressed()) {
    M5.Lcd.println("Blasting...");

    for (int i = 0; i < 3; i++) 
    {
      //Send codes 3 times to cover for any misses
      // NEC (LG/Samsung common)
      irsend.sendNEC(0x20DF10EF, 32);
      delay(50);
      // Sony
      irsend.sendSony(0xA90, 12);
      delay(50);
      // RC5
      irsend.sendRC5(0x0C, 12);
      delay(50);
    }

    M5.Lcd.println("IR Code Blasted");
  }
  M5.update();
}
