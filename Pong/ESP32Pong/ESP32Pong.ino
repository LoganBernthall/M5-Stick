/*
************************************************************
*By - Logan Bernthall 20/02/26
*Pong on ESP32
*Simple Pong Game
************************************************************
*/

#include <M5StickCPlus.h>

//Opponent
int opponentY = 60;     
int opponentSpeed = 2;  
int paddleHeight = 20;

void game()
{
  //Game function

  //Beging making Pong court
  M5.Lcd.fillScreen(BLACK);
  //Middle line
  M5.Lcd.fillRect(115, 115, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 100, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 85, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 70, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 55, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 40, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 25, 5, 10, WHITE);
  M5.Lcd.fillRect(115, 10, 5, 10, WHITE);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  M5.begin();

  //Var Dec
  char greeting[] = "ESP32 Pong!";
  char instrucHome[] = "Press Home To Play";
  //

  //Set portrait
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
  // put your main code here, to run repeatedly:
  M5.update();

    if (M5.BtnA.wasPressed())
    {
    M5.update();
    delay(2000); 
    game();
    }

  // Opponent 
  M5.Lcd.fillRect(230, opponentY, 5, paddleHeight, BLACK);

  // Move paddle
  opponentY += opponentSpeed;

  // Bounce off top and bottom
  if (opponentY <= 0 || opponentY + paddleHeight >= M5.Lcd.height())
  {
    opponentSpeed = -opponentSpeed;
  }

  // Draw new paddle
  M5.Lcd.fillRect(230, opponentY, 5, paddleHeight, WHITE);

  delay(20);  // controls speed


}
