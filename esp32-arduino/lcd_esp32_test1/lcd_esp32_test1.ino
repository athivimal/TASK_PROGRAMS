#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
LiquidCrystal_I2C lcd1(0x3E, 16, 2);
LiquidCrystal_I2C lcd2(0x3D, 16, 2);
LiquidCrystal_I2C lcd3(0x3B, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  lcd3.init();
  lcd3.backlight();
  //delay(2000);
}


void loop()
{
  
  lcd.setCursor(0,0);
  lcd.print("  krish tec ");
  lcd.setCursor(0,1);
  lcd.print("  covAI-lab ");
  lcd1.setCursor(0,0);
  lcd1.print("  karthi  ");
  lcd1.setCursor(0,1);
  lcd1.print("  covAI-lab ");
  lcd2.setCursor(0,0);
  lcd2.print("  giri ");
  lcd2.setCursor(0,1);
  lcd2.print("  covAI-lab ");
  lcd3.setCursor(0,0);
  lcd3.print("  naveena ");
  lcd3.setCursor(0,1);
  lcd3.print("  covAI-lab ");
  delay(1000);
}
