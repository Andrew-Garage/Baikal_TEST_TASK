#include "GyverTimers.h"
#include <Wire.h>
#define A 2 
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP A2
#define D1 12
#define D2 11 
#define D3 10
#define D4 9
char digit[] = {D1,D2,D3,D4};
char segment[] = {A,B,C,D,E,F,G};
int num [][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};
long number = 9876;
int delay_time = 6;
int i = 0;

int N1 = ((number%10000)/1000)%10;
int N2 = ((number%10000)/100)%10;
int N3 = ((number%10000)/10)%10;
int N4 = (number%10000)%10;
int num_div[] = {N1, N2, N3, N4};

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);  
  digitalWrite(D3, HIGH);  
  digitalWrite(D4, HIGH);
  //Serial.begin(9600);
  
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent); 
}

void loop() {
  for(i=0; i<4; i++){
    writeDigit(i, num_div[i]);
  }
}

void writeDigit(int d, int f){
digitalWrite(digit[d], LOW);
  for(int i=0; i<sizeof(segment);i++){
    digitalWrite(segment[i], num[f][i]);
  }
delay(delay_time);
digitalWrite(digit[d], HIGH);
}

void receiveEvent(){
  byte rightVal = 90 - Wire.read();
  byte leftVal = Wire.read() - 90;

  //Serial.print(leftVal);
  //Serial.println(" leftVal");
  //Serial.print(rightVal);
  //Serial.println(" rightVal");

  num_div[0] = leftVal/10;
  num_div[1] = leftVal%10;
  num_div[2] = rightVal/10;
  num_div[3] = rightVal%10;
}
