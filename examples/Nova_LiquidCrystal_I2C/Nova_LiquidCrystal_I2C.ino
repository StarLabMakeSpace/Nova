//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
//#include <Wire.h> 
#include <Nova.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(M1);//C0,C1,M0,M1,M2,M3;
void setup()
{
 lcd.begin();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  //lcd.noBacklight();

}

void loop()
{
  lcd.clear();
  lcd.print("Nice to meet you");
  lcd.setCursor(3,1);
   lcd.print("LCD1602!");

  delay(1000);
  lcd.clear();
   lcd.print("arduino!");
  lcd.setCursor(9,0);
  lcd.print("good!");
  delay(1000);
  
}
