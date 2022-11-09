#include <WiFi.h>

char ssid[] = "BRH_2.4GHZ";
char pass[] = "BeWiFi@here";
void setup()
{
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 delay(100);
 WiFi.begin(ssid, pass);
 delay(5000);
 }

void loop()
 {
  delay(1000);
  if (WiFi.status() != WL_CONNECTED) 
  {
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(ssid, pass);
    delay(5000); // Allowing connection to be established, before reconnecting
  }
  else 
  {
    WiFi.setTxPower(WIFI_POWER_13dBm);
    int a = WiFi.getTxPower();
    Serial.print("TX power:");
    Serial.println(a);
   
    delay(2000);
  }
}
