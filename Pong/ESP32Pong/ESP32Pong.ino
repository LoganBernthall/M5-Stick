/*
************************************************************
*By - Logan Bernthall 20/02/26
*Pong on ESP32
*Simple Pong Game
************************************************************
*/

#include <M5StickCPlus.h>

//Player (ME!)
int playerY = 60;
int playerSpeed = 3;
int playerHeight = 20;

//Opponent
int opponentY = 60;     
int opponentSpeed = 2;  
int paddleHeight = 20;


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
  M5.update();

  // -------- PLAYER CONTROLS --------
  if (M5.BtnA.isPressed())  // Move Up
  {
    playerY -= playerSpeed;
  }

  if (M5.BtnB.isPressed())  // Move Down
  {
    playerY += playerSpeed;
  }

  // Keep player on screen
  if (playerY < 0)
    playerY = 0;

  if (playerY + playerHeight > M5.Lcd.height())
    playerY = M5.Lcd.height() - playerHeight;

  // -------- OPPONENT MOVEMENT --------
  opponentY += opponentSpeed;

  if (opponentY <= 0 || opponentY + paddleHeight >= M5.Lcd.height())
  {
    opponentSpeed = -opponentSpeed;
  }

  // -------- DRAW FRAME --------
  M5.Lcd.fillScreen(BLACK);

  // Middle dotted line
  for (int y = 10; y < 130; y += 15)
  {
    M5.Lcd.fillRect(115, y, 5, 10, WHITE);
  }

  // Draw player (left side)
  M5.Lcd.fillRect(5, playerY, 5, playerHeight, WHITE);

  // Draw opponent (right side)
  M5.Lcd.fillRect(230, opponentY, 5, paddleHeight, WHITE);

  delay(20);
}
