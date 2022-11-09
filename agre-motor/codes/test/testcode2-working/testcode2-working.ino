#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); 
LoRa_E32 e32ttl(&mySerial, D4, D5, D6);
void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, INPUT);
  e32ttl.begin();
  ResponseStatus rs = e32ttl.sendMessage("kt");
  Serial.println(rs.getResponseDescription());
}
void loop() {
  if (e32ttl.available()>1) {
  ResponseContainer rc = e32ttl.receiveMessage();
  String cmd = rc.data;
  if (rc.status.code!=1){
    rc.status.getResponseDescription();
  }else{
    Serial.println(rc.data);
  }
  if (cmd[1]=='n'){
      digitalWrite(D2, HIGH);     
      digitalWrite(D3, LOW);
      delay(10000);
    while (digitalRead(D4)==1){
      digitalWrite(D2, HIGH);     
      digitalWrite(D3, LOW);
      delay(100);
    }
    if (digitalRead(D4)==0){
      digitalWrite(D3, LOW);     
      digitalWrite(D2, LOW);
  }
  }
  if (cmd[1]=='f'){
      digitalWrite(D3, HIGH);     
      digitalWrite(D2, LOW);
      delay(10000);
    while(digitalRead(D4)==1){
      digitalWrite(D3, HIGH);     
      digitalWrite(D2, LOW);
      delay(100);
    }
    if (digitalRead(D4)==0){
      digitalWrite(D3, LOW);     
      digitalWrite(D2, LOW);
    }
  } 
}
}
