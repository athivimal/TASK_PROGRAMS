#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  

void setup()
{
  lcd.init();
  
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  Serial.print("Scan start ... ");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCAN Started..");
  int n = WiFi.scanNetworks();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(n);
  lcd.setCursor(2,0);
  lcd.print("Networks");
  lcd.setCursor(0,1);
  lcd.print("found");
  Serial.print(n);
  Serial.println(" network found");
  delay(2000);
  for (int i = 1; i < n+1; i++)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(i);
    lcd.print(" Network");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.SSID(i-1));
    Serial.println(WiFi.SSID(i-1));
    Serial.print("(");
    Serial.print(WiFi.RSSI(i-1));
    Serial.print(")");
    delay(1000);
  }
  Serial.println();
  delay(3000);
}
