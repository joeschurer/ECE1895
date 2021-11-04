    #include <Wire.h>
     #include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include <MPU6050.h>

//setup LCD and gyro
LiquidCrystal_I2C lcd(0x27,20,4);
     
    void setup()
    {
      Wire.begin();
     lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("uh oh");
  lcd.clear();
      Serial.begin(9600 );
      //while (!Serial);             // Leonardo: wait for serial monitor
      //.println("\nI2C Scanner");
    }
     
     
    void loop()
    {
      byte error, address;
      int nDevices;
     
      Serial.println("Scanning...");
     
      nDevices = 0;
      for(address = 1; address < 127; address++ )
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
     
        if (error == 0)
        {
          Serial.print("I2C device found at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.print(address,HEX);
          lcd.print(address);
          delay(1000);
          lcd.clear();
          Serial.println("  !");
     
          nDevices++;
        }
        else if (error==4)
        {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
          lcd.print(address);
          delay(1000);
          lcd.clear();
        }    
      }
      if (nDevices == 0)
        Serial.println("No I2C devices found\n");
      else
        Serial.println("done\n");
      lcd.print(nDevices);
          delay(1000);
          lcd.clear();
      
      delay(5000);           // wait 5 seconds for next scan
    }

