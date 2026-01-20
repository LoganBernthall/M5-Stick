/*
************************************************************
*By - Logan Bernthall 16/01/26
*WIFI Scanner as my first Arduino Project!
*Probably been made a million times but oh well.
************************************************************
*/

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <WiFiMulti.h>

void drawWifiIcon(int cx, int cy, uint16_t color) {
  // Dot
  M5.Lcd.fillCircle(cx, cy + 12, 3, color);

  // Signal rings
  M5.Lcd.drawCircle(cx, cy + 12, 18, color);
  M5.Lcd.drawCircle(cx, cy + 12, 12, color);
  M5.Lcd.drawCircle(cx, cy + 12, 6, color);

  // Mask bottom half to fake arcs
  M5.Lcd.fillRect(cx - 20, cy + 12, 40, 20, BLACK);
}

void buttonStart(){
  //Fucntion to proceed from start menu

  //Variable declaration
  char startScan[] = "Scanning...";
  char stopScan[] = "Hold B button to cancel";
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 30);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print(startScan);
  M5.Lcd.setCursor(10, 60);
  M5.Lcd.setTextSize(1);
  M5.Lcd.print(stopScan);
}

void scan(){
  //Function to scan WiFi networks
  M5.Lcd.fillScreen(BLACK);

  //Ensure WiFi is on station mode and M5Stick is disconnected from anything
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  //Begin scanner
  int scanW = WiFi.scanNetworks();

  //Set screen params
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(5, 5);

int maxToShow = 5;

  if (scanW == 0) {
    M5.Lcd.print("No networks found");
  } else {
    int count = min(scanW, maxToShow);

    for (int i = 0; i < count; i++) {
      M5.Lcd.printf(
        "%d:%s\n%d dBm %s\n\n",
        i + 1,
        WiFi.SSID(i).c_str(),
        WiFi.RSSI(i),
        (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Sec"
      );
    }
  }
}

void buttonCancel(){
  //Function to cancel scan
  
}

void setup() {
  //Start
  Serial.begin(115200);
  M5.begin();
  
  //Variable declaration
  char greeting[] = "M5Stick WiFi Scanner";
  char instrucHome[] = "Press Home To Scan";
  int cx = M5.Lcd.width() / 2;
  int iconY = 40;
  int screenW = M5.Lcd.width();
  int screenH = M5.Lcd.height();
  int centerX = screenW / 2;
  int logoY = 40; //Change to move
  int logoX = (screenW / 2) + 50; //Change 50 to move right
  //Setting portrait landscape
  M5.Lcd.setRotation(3);
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  
  //Input logo
  drawWifiIcon(logoX, logoY, BLUE);  
  
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
  
  if (M5.BtnA.wasPressed()){
    buttonStart();
    M5.update();
    delay(2000); 
    scan();
}

  if(M5.BtnB.pressedFor(100)){
    setup();
  } 
  M5.update();



}
