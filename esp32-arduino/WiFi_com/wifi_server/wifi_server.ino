#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Wire.h>
// Replace with your network credentials
const char* ssid = "BRH_2.4GHZ";
const char* password = "BeWiFi@here";
// Set web server port number to 80
AsyncWebServer server(80);
String message="hello";
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", message.c_str());
  });
  delay(100);
{
  message = Serial.read();
}
}
