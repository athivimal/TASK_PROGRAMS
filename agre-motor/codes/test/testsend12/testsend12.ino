#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial, D4, D5, D6);
void setup() {
  Serial.begin(9600);
  delay(500);
  e32ttl.begin();

}
void loop() {
  ResponseStatus rs = e32ttl.sendMessage("M1");
  Serial.println(rs.getResponseDescription());
  delay(1000);
}
