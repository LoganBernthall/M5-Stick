#include <WiFi.h>
#include <WebServer.h>



WebServer server(80);

void setup() {
  WiFi.softAP("TestAP", "12345678");

  server.on("/", []() {
    server.send(200, "text/plain", "Hello from ESP32");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}