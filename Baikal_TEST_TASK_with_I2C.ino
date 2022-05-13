#include <Servo.h>
#include <Wire.h>

#define rightBtn 2
#define leftBtn  3
#define rightPot A0
#define leftPot  A1
int arrowPos = 90;
int leftPos;
int rightPos;
Servo arrow; 

void setup() {
  pinMode(rightBtn, INPUT);
  pinMode(leftBtn, INPUT);
  arrow.attach(10);
  
  Wire.begin();
    for(int i = 0; i<=180; i++){
      arrow.write(i);
      if(i==0) delay(500);
      delay(5);
    }
  
    for(int i = 180; i>=0; i--){
      arrow.write(i);
      delay(5);
      if(i==0) delay(500);
    }
  arrow.write(90);
  //Serial.begin(9600);
}

void setAngle() {
  //Serial.print("LEFT: ");
  leftPos = (analogRead(leftPot)*9)/100;  // реальная позиция 90 - 180
    if(leftPos > 90) leftPos = 90;  // округляем
  //Serial.println(90 - leftPos);  // пишем мнимое 0 - 90 (по часовой)
  
  //Serial.print("RIGHT: ");
  rightPos = 90 + (analogRead(rightPot)*9)/100;  // реальная позиция 90 - 180
     if(rightPos > 180) rightPos = 180; // округляем
  //Serial.println(rightPos - 90);  // пишем мнимое 0 - 90 (по часовой)
  
  Wire.beginTransmission(8);
  Wire.write(leftPos);
  Wire.write(rightPos);
  Wire.endTransmission();
}

void loop() {
  if(digitalRead(leftBtn) == HIGH){
    arrow.write(leftPos);
  }
  
  if(digitalRead(rightBtn) == HIGH){
    arrow.write(rightPos);
  }
  setAngle();
  delay(100);
}
