#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); 
LoRa_E32 e32ttl(&mySerial, D4, D5, D6);
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, INPUT);
  e32ttl.begin();
  ResponseStructContainer c;
  c = e32ttl.getConfiguration();
  Configuration configuration = *(Configuration*) c.data;
  configuration.ADDL = 0x0;
  configuration.ADDH = 0x0;
  configuration.CHAN = 0x17;
  configuration.OPTION.fec = FEC_0_OFF;
  configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
  configuration.OPTION.transmissionPower = POWER_20;
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;
  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;
  ResponseStatus rs = e32ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);
  Serial.println(rs.getResponseDescription());
  Serial.println(rs.code);
  printParameters(configuration);
  c.close();
  ResponseStatus r = e32ttl.sendMessage("kt");
  Serial.println(r.getResponseDescription());
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
void printParameters(struct Configuration configuration) {
  Serial.println("----------------------------------------");

  Serial.print(F("HEAD : "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
  Serial.println(F(" "));
  Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, DEC);
  Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, DEC);
  Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
  Serial.println(F(" "));
  Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
  Serial.print(F("SpeedUARTDatte  : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
  Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

  Serial.print(F("OptionTrans        : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
  Serial.print(F("OptionPullup       : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
  Serial.print(F("OptionWakeup       : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
  Serial.print(F("OptionFEC          : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
  Serial.print(F("OptionPower        : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

  Serial.println("----------------------------------------");

}
