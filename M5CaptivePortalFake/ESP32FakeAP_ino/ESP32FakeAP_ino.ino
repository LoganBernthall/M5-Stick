
#include <M5StickCPlus.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <esp_wifi.h>
// Fix macro conflict
#undef min
#undef max
//

//
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

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

<form action="/get">
<input type="text" name="username" placeholder="Username"><br>
<input type="password" name="password" placeholder="Password"><br>
<button type="submit">Login</button>
</form>

</div>

</body>
</html>
)=====";

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html); 
  }

};

void setupServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send_P(200, "text/html", index_html); 
      Serial.println("Client Connected");
  });

  // Android
  server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(204);  // IMPORTANT: must be 204
  });

  // Apple (iOS/macOS)
  server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", index_html);
  });

  // Windows
  server.on("/ncsi.txt", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/plain", "Microsoft NCSI");
  });
  
  //Std push
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request)
  {
      String inputMessage;
      String inputParam;
  
      if (request->hasParam("name")) 
      {
        inputMessage = request->getParam("name")->value();
        inputParam = "name";
        user_name = inputMessage;
        Serial.println(inputMessage);
        name_received = true;
      }

      if (request->hasParam("proficiency"))
      {
        inputMessage = request->getParam("proficiency")->value();
        inputParam = "proficiency";
        proficiency = inputMessage;
        Serial.println(inputMessage);
        proficiency_received = true;
      }

      server.onNotFound([](AsyncWebServerRequest *request)
      {
      request->redirect("/");
      });

      request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>");
  });

}

void showClients() {
  wifi_sta_list_t wifi_sta_list;
  esp_wifi_ap_get_sta_list(&wifi_sta_list);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(1);

  M5.Lcd.println("Connected Clients:");
  M5.Lcd.printf("Count: %d\n\n", wifi_sta_list.num);

  for (int i = 0; i < wifi_sta_list.num; i++) {
    wifi_sta_info_t station = wifi_sta_list.sta[i];

    M5.Lcd.printf("%d: MAC ", i + 1);

    for (int j = 0; j < 6; j++) {
      M5.Lcd.printf("%02X", station.mac[j]);
      if (j < 5) M5.Lcd.print(":");
    }

    M5.Lcd.println();
  }

}

void setup() 
{
  //Start
  Serial.begin(115200);
  M5.begin();
  
  //Variable declaration
  char intro[] = "M5Stick Capitve";
  char greeting[] = "Portal AP";
  
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

  Serial.println();
  Serial.println("Setting up AP Mode");
  WiFi.mode(WIFI_AP); 
  WiFi.softAP("Super WiFi");
  Serial.print("AP IP address: ");Serial.println(WiFi.softAPIP());
  Serial.println("Setting up Async WebServer");
  setupServer();
  Serial.println("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...
  server.begin();
  Serial.println("All Done!");

}

void loop() 
{
    M5.update();
    dnsServer.processNextRequest(); 

    //Process Requests
      dnsServer.processNextRequest();
    if(name_received && proficiency_received){
        Serial.print("Hello ");Serial.println(user_name);
        Serial.print("You have stated your proficiency to be ");Serial.println(proficiency);
        name_received = false;
        proficiency_received = false;
        Serial.println("We'll wait for the next client now");
      }
 
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000)
  { // update every 2 sec
    showClients();
    lastUpdate = millis();
  }

}