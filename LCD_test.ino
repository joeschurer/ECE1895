#include <SparkFun_Qwiic_Twist_Arduino_Library.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include <MPU6050.h>

//setup LCD and gyro
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_MPU6050 mpu;
TWIST twist;

//game variables
char shake_message[] = "Shake it!";
char pour_message[] = "Pour it!";
char twist_message[] = "Twist it!";
float X, Y, Z, totalAccel;
int currTask = 0;//0 place, 1 shake, 2 stir
int oldPos = 0;
int tasks[3] = {-1,-1,-1};
int score = 0;
int started = -1;

#define ROLL_THRESHOLD  15

void setup() {
  pinMode(8, OUTPUT);
  pinMode(12, INPUT);
  digitalWrite(12,HIGH);//make pull up
  pinMode(10 , OUTPUT);

  //LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.clear();
  //lcd.print("TEST");

  //Detect gyro
  while (!mpu.begin()) {
   // Serial.println("MPU6050 not connected!");
    lcd.print("mstuck");
    delay(1000);
  }

  //setup twist
  while(twist.begin()==false){
    lcd.print("tstuck");
    delay(1000);
  }
  
  lcd.clear();
  //Serial.println("MPU6050 ready!");
  
  
}
sensors_event_t event;


void loop() {
  //detect start switch
  //delay(5000);
  if(started == -1){
    if(digitalRead(12) == LOW){
      lcd.print("working");
      delay(1000);
      lcd.clear();
      //tone(10,1000,20);
      //digitalWrite(8,HIGH);
      started = 1;
    }
  }

  if(started == 1){
    
    //digitalWrite(8,HIGH);
    //lcd.clear();
    //lcd.print("entered");
    X = 0;
    Y = 0;
    Z = 0;
    for (int i=0; i<10; i++) {
      mpu.getAccelerometerSensor()->getEvent(&event);
      X += event.acceleration.x;
      Y += event.acceleration.y;
      Z += event.acceleration.z;
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;
  
    totalAccel = sqrt(X*X + Y*Y + Z*Z);
    
    Z = event.acceleration.z;

    //test total accel
    /*lcd.print(totalAccel);
    delay(1000);
    lcd.clear();
    */

    //test twist count
    lcd.print(twist.getDiff());
    delay(1000);
    lcd.clear();
    
    
    if(Z<-6){
      lcd.setCursor(1,0);
      lcd.print("upside down");
      tone(10,1000,20);
      delay(1000);
      lcd.clear();
      digitalWrite(8,HIGH);
    }
  
    if (totalAccel > ROLL_THRESHOLD) {
      //Serial.println("Shaking");
      lcd.setCursor(1,0);
      lcd.print("Shaking");
      delay(1000);
      lcd.clear();
    }
  
  }
  
}
  while(twist.begin()==false){
    lcd.print("tstuck");
    delay(1000);
  }
  
  lcd.clear();
  //Serial.println("MPU6050 ready!");
  
  
}
sensors_event_t event;


void loop() {
  //detect start switch
  //delay(5000);
  if(started == -1){
    if(digitalRead(12) == LOW){
      lcd.print("working");
      delay(1000);
      lcd.clear();
      //tone(10,1000,20);
      //digitalWrite(8,HIGH);
      started = 1;
    }
  }

  if(started == 1){
    
    //digitalWrite(8,HIGH);
    //lcd.clear();
    //lcd.print("entered");
    X = 0;
    Y = 0;
    Z = 0;
    for (int i=0; i<10; i++) {
      mpu.getAccelerometerSensor()->getEvent(&event);
      X += event.acceleration.x;
      Y += event.acceleration.y;
      Z += event.acceleration.z;
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;
  
    totalAccel = sqrt(X*X + Y*Y + Z*Z);
    
    Z = event.acceleration.z;

    //test total accel
    /*lcd.print(totalAccel);
    delay(1000);
    lcd.clear();
    */

    //test twist count
    lcd.print(twist.getDiff());
    delay(1000);
    lcd.clear();
    
    
    if(Z<-6){
      lcd.setCursor(1,0);
      lcd.print("upside down");
      tone(10,1000,20);
      delay(1000);
      lcd.clear();
      digitalWrite(8,HIGH);
    }
  
    if (totalAccel > ROLL_THRESHOLD) {
      //Serial.println("Shaking");
      lcd.setCursor(1,0);
      lcd.print("Shaking");
      delay(1000);
      lcd.clear();
    }
  
  }
  
}
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
