#include <SparkFun_Qwiic_Twist_Arduino_Library.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
unsigned long myTime;

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
int interval = 20000;
unsigned long prevTime;

#define ROLL_THRESHOLD  15

void setup() {
  pinMode(8, OUTPUT);
  pinMode(0, INPUT);
  //digitalWrite(0,HIGH);//make pull up
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
  twist.setColor(100, 10, 50);
}
sensors_event_t event;

void announceTask(int task){
  lcd.clear();
  lcd.print(taskStrings[task]);
  tone(10,taskTones[task],2);//check for the right pin here
  twist.setColor(100, 10, 50);
  
}

void compTask(int task){
  if(task == currTask){
    score++;
    twist.setColor(0, 255, 0);
    lcd.clear();
    lcd.print("SUCCESS!");
  } else {
    fails++;
    lcd.clear();
    lcd.print("FAIL!");
    tone(10,3000,5);
    twist.setColor(255,0,0);
  }
  delay(1000);
  comp =1;
  interval = interval -800;
}
void loop() {
  //detect start switch
  if(started == -1){
    if(digitalRead(0) == LOW){
      lcd.print("starting..");
      delay(1000);
      lcd.clear();
      //tone(10,1000,20);
      //digitalWrite(8,HIGH);
      started = 1;
    } else {
      lcd.print("not started");
      delay(1000);
      lcd.clear();
    }
  }

  if(started==1){
    if((fails==0) && score <5){
      //generate task
      int diff=twist.getDiff();
      currTask = random(0,3);
      announceTask(currTask);
      delay(2000);
      
      comp =-1;
      prevTime = millis();
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
       // lcd.print(twist.getDiff());
       // delay(1000);
       // lcd.clear();
        
        diff = twist.getDiff();
        myTime = millis();
        if(myTime > (prevTime + interval)){
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Time's Up!");
          tone(10,1000,20);
          delay(1000);
          compTask(-1);
        }
        else if(diff!=0){
            //task completed check if correct one
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Stired!");
            tone(10,1000,20);
            delay(1000);
            lcd.clear();
            compTask(2);
        } else if(Z<-8){
            //task completed check if correct one
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Poured!");
          tone(10,1000,20);
          delay(1000);
          lcd.clear();
   
          compTask(1);;
        }else if (totalAccel > ROLL_THRESHOLD) {
            //task completed check if correct one
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Shaking!");
          delay(1000);
          lcd.clear();
          
          compTask(0);
        }
      
      }
    }else{
      lcd.clear();
      lcd.setCursor(1,0);
      if(fails==1){
        lcd.print("YOU LOST");
        lcd.setCursor(1,1);
        lcd.print("SCORE: ");
        lcd.print(score);
        twist.setColor(255, 0, 0);
      } else {
        lcd.print("WIN!!");
        lcd.setCursor(1,1);
        lcd.print("SCORE: ");
        lcd.print(score);
        twist.setColor(0, 255, 0);
      }
      delay(5000);
    }
  }
}
