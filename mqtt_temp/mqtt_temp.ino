#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define DHTPIN 15
#define DHTTYPE DHT11

long lastMsg = 0;
char msg[50];
int value = 0;
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "BRH_2.4GHZ";
const char* password = "BeWiFi@here";
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {   
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    int t = dht.readTemperature();
    String k = String(t)+"°C";
    char i[8];
    strcpy (i, k.c_str());
    int h = dht.readHumidity();
    String l = String(h)+"%";
    char j[8];
    strcpy (j, l.c_str());
  //Serial.println(i);
  //Serial.println(j);
    Serial.print("Temperature: ");
    Serial.println(i);
    client.publish("esp32/temperature", i);
    Serial.print("Humidity: ");
    Serial.println(j);
    client.publish("esp32/humidity", j);
  }
}
