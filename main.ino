#include <SparkFun_Qwiic_Twist_Arduino_Library.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


//setup LCD and gyro
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_MPU6050 mpu;
TWIST twist;

//game variables
char shake_message[] = "Shake it!";
char pour_message[] = "Pour it!";
char twist_message[] = "Twist it!";
char *taskStrings[] = {"Shake it!","Pour it!","Twist it!"};
int taskTones[] = {1000,1500,2000};
float X, Y, Z, totalAccel;
int currTask = 0;//0 pour, 1 shake, 2 stir
int oldPos = 0;
int tasks[3] = {-1,-1,-1};
int score = 0;
int fails = 0;
int started = -1;
int comp = -1;

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
    lcd.print("mstuck");
    delay(1000);
  }

  //setup twist
  while(twist.begin()==false){
    lcd.print("tstuck");
    delay(1000);
  }
  
  lcd.clear();
  randomSeed(analogRead(0));
}
sensors_event_t event;


void loop() {
  //detect start switch
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

  if(started == 1 && (fails!=3) && score <99){
    
    //digitalWrite(8,HIGH);
    //lcd.clear();
    //lcd.print("entered");

    //generate task
    currTask = random(0,2);
    announceTask(currTask);
    int comp =-1;
    
    while(comp == -1){  
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
      
      int diff = twist.getDiff();
  
      if(diff>10){
          //task completed check if correct one
          compTask(2);
      } else if(Z<-6){
          //task completed check if correct one
        /*lcd.setCursor(1,0);
        lcd.print("upside down");
        tone(10,1000,20);
        delay(1000);
        lcd.clear();
        digitalWrite(8,HIGH);
        */
        compTask(0);;
      }else if (totalAccel > ROLL_THRESHOLD) {
          //task completed check if correct one
        /*lcd.setCursor(1,0);
        lcd.print("Shaking");
        delay(1000);
        lcd.clear();
        */
        compTask(1);
      }
    
    }
  }

  lcd.clear();
  if(score>=99){
    lcd.print("WIN!!");
  } else {
    lcd.print("YOU LOST");
  }
  delay(5000);
}

void announceTask(int task){
  lcd.clear();
  lcd.print(taskStrings[task]);
  tone(10,taskTones[task],2);//check for the right pin here
  
}

void compTask(int task){
  if(task == currTask){
    score++;
  } else {
    fails++;
    lcd.clear();
    lcd.print("FAIL!");
    tone(10,3000,5);
  }

  comp =1;
}
