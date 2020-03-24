#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(3,0);
  lcd.print("Hello,");
  lcd.setCursor(7,1);
  lcd.print("World!");
}


void loop()
{
}
