#include "WiFi.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

const char* ssid = "KRISHTEC";
const char* password =  "KRISHtec@5747";
//char msg[60];
String mystring="";
WiFiServer wifiServer(8090);
void handleReceivedMessage(String message){
 
  StaticJsonBuffer<500> JSONBuffer;                     //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(message); //Parse message
 
  if (!parsed.success()) {   //Check for errors in parsing
 
    Serial.println("Parsing failed");
    return;
 
  }
  const char * a = parsed["a"];          
  const char * b = parsed["b"]; 
  int c = parsed["c"];                        
  LiquidCrystal_I2C lcd(c, 16, 2);
  lcd.clear();
  Serial.print("a: ");
  Serial.println(a);
  Serial.print("b: ");
  Serial.println(b);
  Serial.print("c: ");
  Serial.println(c);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print(b);
  delay(100);
}
void setup() {
 
 Serial.begin(115200);
 for (int c=56;c<=63;c++)
  {
    LiquidCrystal_I2C lcd(c, 16, 2);
    lcd.init();
  }
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
       /* for(int x=0;x<=60;x++){
          msg[x]= client.read();
          delay(10);
        }*/
      for(int x=0;x<=60;x++){
      char msg= client.read();
      Serial.println(msg);
      mystring+=msg;
      Serial.println(mystring);
      }
      if (mystring.length()<63)
      {
      handleReceivedMessage(mystring);
      }
      }
      delay(10);
    }
    client.stop();
    Serial.println("Client disconnected");
    mystring="";
  }
}
