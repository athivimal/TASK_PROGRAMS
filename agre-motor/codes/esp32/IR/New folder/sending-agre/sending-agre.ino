#include "Arduino.h"
#include "LoRa_E32.h"
#define BLYNK_TEMPLATE_ID "TMPLzr33aJv2"
#define BLYNK_DEVICE_NAME "VALVE"
#define BLYNK_AUTH_TOKEN "HTTJK-SRE7Wmh-7n31hgGl0atuolW7Yy"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KRISH_ACT_GCT";
char pass[] = "superACT2009";

BlynkTimer timer;
BLYNK_CONNECTED()
{
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
#include <HardwareSerial.h>
HardwareSerial mySerial(2); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial, 5, 18, 19);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  delay(500);
  lcd.init();
  lcd.backlight();
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
  ResponseStatus r = e32ttl.sendMessage("ready");
  Serial.println(r.getResponseDescription());
}
BLYNK_WRITE(V0)
{
if(param.asInt() == 1)
  {
    Serial.println(param.asInt()+"motor");
    digitalWrite(4,HIGH);  
    digitalWrite(2,HIGH);
    digitalWrite(15,HIGH);
    lcd.setCursor(6,1);
    lcd.print("ON ");
  }
  else
  {
    digitalWrite(4,LOW); 
    digitalWrite(2,LOW);
    digitalWrite(15,LOW);
    lcd.setCursor(6,1);
    lcd.print("OFF");    
  }
}
BLYNK_WRITE(V1)
{
  Serial.println(param.asInt()+"pump");
if(param.asInt() == 1)
  {
    e32ttl.sendMessage("on");
    lcd.setCursor(14,1);
    lcd.print("on");
  }
  else
  {
    e32ttl.sendMessage("off");
    lcd.setCursor(14,1);
    lcd.print("off");    
  }
}
void loop() {
  Blynk.run();
  timer.run();
  lcd.setCursor(0,0);
  lcd.print("Channel:0x17");
  lcd.setCursor(0,1);
  lcd.print("Motor:OFF");
  lcd.setCursor(9,1);
  lcd.print("Data:");
  if (e32ttl.available()>1) {
    // read the String message
  ResponseContainer rc = e32ttl.receiveMessage();
  // Is something goes wrong print error
  if (rc.status.code!=1){
    rc.status.getResponseDescription();
  }else{
    Serial.println(rc.data);
    lcd.setCursor(14,1);
    lcd.print(rc.data);
  }
  }
  if (Serial.available()) {
    String input = Serial.readString();
    e32ttl.sendMessage(input);
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
