#include <LiquidCrystal.h>

//#include "Arduino.h"
//#include "Button.h"
#include <Servo.h>
LiquidCrystal lcd(1,2,4,5,6,7);
const int knapp = 3;
int ButtonState = 0;         // current state of the button
int oldButtonState = 0;
const int ledPin1 = 10; 
const int ledPin2 = 11; 
const int buzz1 = 12; 
const int buzz2 = 13; 
const int plasticsensor=A0;
int metalsensor= A1;
int metalsensor_M= A2;
Servo myservo;
Servo myservo_M;
int pos = 90;
int pos_M = 360;



void setup() {
  pinMode(knapp, INPUT);
  digitalWrite(knapp, LOW); 
lcd.begin(16,2);
lcd.clear();

 myservo.attach(9);
 myservo_M.attach(8);
   pinMode(plasticsensor,INPUT_PULLUP);
   pinMode(metalsensor,INPUT_PULLUP);
   pinMode(metalsensor_M,INPUT_PULLUP);
   pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
   pinMode(buzz1, OUTPUT);
   pinMode(buzz2, OUTPUT);
  
   Serial.begin(9600);
}

   void loop() {
    lcd.setCursor(0,0);
  lcd.print("INSERT METAL ON");
  lcd.setCursor(0,1);
  lcd.print("   RIGHT SIDE ");
  delay(6000);
  lcd.clear();
  int sensor_read=digitalRead(plasticsensor);
  Serial.println("plastic sensor");
  Serial.println(sensor_read);
  //delay (10);
  int sensor_read_m=digitalRead(metalsensor);
   //Plastic bin
   Serial.println("metal sensor1");
  Serial.println(sensor_read_m);
  //delay (10);
   int sensor_read_mm=digitalRead(metalsensor_M);
   Serial.println(sensor_read_mm);
   //delay (10);

   

  if((sensor_read==1)&&(sensor_read_m!=1)){
   for (pos = 90; pos <=240; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
     // tell servo to go to position in variable 'pos'
    //delay(5);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(buzz1, HIGH);
    
   // waits 15ms for the servo to reach the position
     }
     //delay(5000);
     for (pos = 240; pos >=90; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    //delay(5);
      
  }
  }
  else {
      // goes from 180 degrees to 0 degr
   
    myservo.write(pos);
    digitalWrite(ledPin1, LOW);
    digitalWrite(buzz1, LOW);
  }
  
  if((sensor_read_mm==1)&&(sensor_read==0)){
    for (pos_M =360; pos_M >= 50; pos_M -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo_M.write(pos_M);   
    
    //delay(5);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(buzz2, HIGH);
    }
    // tell servo to go to position in variable 'pos'
   // delay(5000); 
     for (pos_M = 50; pos_M <=360; pos_M += 1) { // goes from 180 degrees to 0 degrees
    myservo_M.write(pos_M);              // tell servo to go to position in variable 'pos'
    //delay(5);// waits 15ms for the servo to reach the position
     }
  }   
  else{ myservo_M.write(pos_M);
    digitalWrite(ledPin2, LOW);
     digitalWrite(buzz2, LOW);
  }
  } 
   
