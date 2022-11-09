#include <WiFi.h>
#include <ArduinoJson.h>
const char* ssid = "KRISHTEC";
const char* password =  "KRISHtec@5747";
 
const uint16_t port = 8090;
const char * host = "192.168.0.106";
char JSONMessage[] = " {\"a\": \"  karthi  \",\"b\": \"  covai_labs  \", \"c\": 63}";
void setup()
{
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
    client.print(JSONMessage);
    delay(100);
    Serial.println("Disconnecting...");
    client.stop();
    delay(10000);
}
