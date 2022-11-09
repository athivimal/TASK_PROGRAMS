#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial, D4, D5, D6);
void setup() {
  Serial.begin(9600);
  delay(500);
  e32ttl.begin();
  ResponseStatus rs = e32ttl.sendMessage("hi");
  Serial.println(rs.getResponseDescription());
}
void loop() {
	// If something available
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
  e32ttl.sendMessage("1");
  delay(2000);
  e32ttl.sendMessage("2");
  delay(2000);
  e32ttl.sendMessage("3");
  delay(2000);
  if (Serial.available()) {
	  String input = Serial.readString();
	  e32ttl.sendMessage(input);
  }
}
