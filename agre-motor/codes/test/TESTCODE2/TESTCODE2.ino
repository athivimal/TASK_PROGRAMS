#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8);
LoRa_E32 e32ttl(&mySerial, D6, D3, D4);
void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
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
  if (cmd[0]=='1'){
    digitalWrite(D0, HIGH);  
  delay(1000);   
  digitalWrite(D0, LOW);   
  delay(1000);
  }
  if (cmd[0]=='2'){
    digitalWrite(D1, HIGH);  
  delay(1000);   
  digitalWrite(D1, LOW);   
  delay(1000);
  }
  if (cmd[0]=='3'){
    digitalWrite(D2, HIGH);  
  delay(1000);   
  digitalWrite(D2, LOW);   
  delay(1000);
  }
  } 
  if (Serial.available()) {
    String input = Serial.readString();
    e32ttl.sendMessage(input);
  }
}
