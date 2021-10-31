#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_MPU6050 mpu;

char shake_message[] = "Shake it!";
char pour_message[] = "Pour it!";
char twist_message[] = "Twist it!";

#define ROLL_THRESHOLD  20

float X, Y, Z, totalAccel;
void setup()
{
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);

  Serial.begin(115200);

  while (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  Serial.println("MPU6050 ready!");
}
sensors_event_t event;

void loop()
{
  /*
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
  */

  //
  mpu.getAccelerometerSensor()->getEvent(&event);

  Serial.print("[");
  Serial.print(millis());
  Serial.print("] X: ");
  Serial.print(event.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  X = 0;
  Y = 0;
  Z = 0;
  for (int i=0; i<10; i++) {
    X += event.acceleration.x;
    Y += event.acceleration.y;
    Z += event.acceleration.z;
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;

  totalAccel = sqrt(X*X + Y*Y + Z*Z);
  Serial.println("total accel:");
  Serial.println(totalAccel);
  
  Z = event.acceleration.z;
  if(Z< -8){
    Serial.println("upside down");
    lcd.setCursor(1,0);
    lcd.print("upside down");
  }

  if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("Shaking");
    lcd.setCursor(1,0);
    lcd.print("Shaking");
  }
  delay(500);
  
}
