#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char shake_message[] = "Shake it!";
char pour_message[] = "Pour it!";
char twist_message[] = "Twist it!";


void setup()
{
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  //lcd.print("hello everyone");
  //lcd.setCursor(1,1);
  //lcd.print("test");
}


void loop()
{
  lcd.setCursor(1,0);
  lcd.print(shake_message);

  delay(1000);
  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print(pour_message);
  
  delay(1000);
  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print(twist_message);
  delay(1000);
  lcd.clear();
}

