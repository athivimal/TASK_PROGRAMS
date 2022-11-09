#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#define BLYNK_TEMPLATE_ID "TMPLzr33aJv2"
#define BLYNK_DEVICE_NAME "VALVE"
#define BLYNK_AUTH_TOKEN "HTTJK-SRE7Wmh-7n31hgGl0atuolW7Yy"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "KRISH_ACT_GCT";
char pass[] = "superACT2009";

BlynkTimer timer;
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

SoftwareSerial mySerial(D7, D8); 
LoRa_E32 e32ttl(&mySerial, D4, D5, D6);
void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  delay(500);
  e32ttl.begin();
}
BLYNK_WRITE(V0)
{
if(param.asInt() == 1)
  {
    Serial.println(param.asInt()+"motor");
    digitalWrite(D0,HIGH);  
    digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
  }
  else
  {
    digitalWrite(D0,LOW); 
    digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);    
  }
}
BLYNK_WRITE(V1)
{
  Serial.println(param.asInt()+"pump");
if(param.asInt() == 1)
  {
    e32ttl.sendMessage("on");
  }
  else
  {
    e32ttl.sendMessage("off");    
  }
}
void loop() {
	Blynk.run();
  timer.run();
  if (e32ttl.available()>1) {
	  // read the String message
	ResponseContainer rc = e32ttl.receiveMessage();
	// Is something goes wrong print error
	if (rc.status.code!=1){
		rc.status.getResponseDescription();
	}else{
		Serial.println(rc.data);
	}
  }
  if (Serial.available()) {
	  String input = Serial.readString();
	  e32ttl.sendMessage(input);
  }
}
