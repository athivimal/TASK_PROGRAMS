#include "Arduino.h"
#define BLYNK_TEMPLATE_ID "TMPLtytrw0FG"
#define BLYNK_DEVICE_NAME "MOBILE SWITCH"
#define BLYNK_AUTH_TOKEN "KnWCAAiMUWs8XbiJqF2tHBpAjqfEVUSn"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Sara";
char pass[] = "badwolfff";
void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  delay(500);
}
BLYNK_WRITE(V0)
{
if(param.asInt() == 1)
  {
    Serial.println(param.asInt()+" LED1");
    digitalWrite(D0,HIGH);
  }
  else
  {
    digitalWrite(D0,LOW);
  }
}
BLYNK_WRITE(V1)
{
if(param.asInt() == 1)
  {
    Serial.println(param.asInt()+" LED2");
    digitalWrite(D1,HIGH);
  }
  else
  {
    digitalWrite(D1,LOW);
  }
}
BLYNK_WRITE(V2)
{
if(param.asInt() == 1)
  {
    Serial.println(param.asInt()+" LED3");
     digitalWrite(D2,HIGH);
  }
  else
  {
    digitalWrite(D2,LOW);
  }
}
void loop() {
  Blynk.run();
}
