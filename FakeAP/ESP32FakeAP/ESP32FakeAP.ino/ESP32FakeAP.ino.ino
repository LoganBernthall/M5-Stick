
#include <M5StickCPlus.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

//Global vars
DNSServer dnsServer;
AsyncWebServer server(80);

String user_name;
String proficiency;
bool name_received = false;
bool proficiency_received = false;

//HTML Page to serve
const char index_html[] PROGMEM =  R"=====( 
<!DOCTYPE html>
<html>
<head>
<title>WiFi!</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body{
  font-family: Arial;
  text-align:center;
  background:#111;
  color:white;
  margin-top:50px;
}

.box{
  background:#222;
  padding:20px;
  border-radius:10px;
  display:inline-block;
}

input{
  padding:10px;
  margin:10px;
  border:none;
  border-radius:5px;
}

button{
  padding:10px 20px;
  border:none;
  border-radius:5px;
  background:#00bcd4;
  color:white;
  font-size:16px;
}
</style>
</head>

<body>

<div class="box">
<h2>Welcome</h2>
<p>Login to continue</p>

<form action="/login">
<input type="text" name="username" placeholder="Username"><br>
<input type="password" name="password" placeholder="Password"><br>
<button type="submit">Login</button>
</form>

</div>

</body>
</html>
)=====";

void setup() {

  //Start
  Serial.begin(115200);
  M5.begin();
  
  //Variable declaration
  char intro[] = "M5Stick Capitve";
  char greeting[] = "Portal AP";
  char instrucHome[] = "Press Home To Start";

  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(0xe20c);
  M5.Lcd.setTextSize(2); 

  M5.Lcd.setTextDatum(MC_DATUM);   // Middle-center anchor
  M5.Lcd.drawString(intro,
                  M5.Lcd.width() / 2,
                  M5.Lcd.height() / 2 + 5);
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

