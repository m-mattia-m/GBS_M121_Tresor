/*
 * Settings: (Digital-Input)
 * Display : d2
 * Display : d3
 * Display : d4
 * Display : d5
 * Btn R   : d6
 * Btn D   : d7
 * Btn 1   : d8
 * Btn 2   : d9
 * Btn 3   : d10
 * Display : d11
 * Display : d12
 * Btn 4   : d13
 * 
 * Piezo   : a1
 * LED     : a2
 * 
 * 
 * 6 Input | 3 Output
*/

#include <LiquidCrystal.h>

int code[] = {1,2,3,4};
int wrongAttempts = 0;
int userCode[4];
 
int btn1 = 8;
int btn2 = 0;
int btn3 = 10;
int btn4 = 13;
int btnReset = 6;
int btnDelete = 7;

int piezo = 1;
int ledRed = 2;
int ledGreen = 3;
int ledBlue = 4;

int d1 = 2, d2 = 3, d3 = 4, d4 = 5, d5 = 11, d6 = 12;
LiquidCrystal lcd(d1, d2, d3, d4, d5, d6);

int val1 = 1;
int val2 = 2;
int val3 = 3;
int val4 = 4;

void setup(){
    pinMode(btn1, INPUT);
    pinMode(btn2, INPUT);
    pinMode(btn3, INPUT);
    pinMode(btn4, INPUT);
    pinMode(btnReset, INPUT);
    pinMode(btnDelete, INPUT);
    lcd.begin(16, 2);

    
    // pinMode(led, OUTPUT);
    // pinMode(piezo, OUTPUT);
}

void loop(){
  if(digitalRead(btn1)){
    userCode[sizeof(userCode)] = 1;
    Serial.print("test_works")
  }
  if(digitalRead(btn2)){
    userCode[sizeof(userCode)] = 2;
  }
  if(digitalRead(btn3)){
    userCode[sizeof(userCode)] = 3;
  }
   if(digitalRead(btn4)){
    userCode[sizeof(userCode)] = 4;
  }

  if(sizeof(userCode) == 4){
    for(int i = 0; i < 4; i++) {
      if(userCode[i] != code[i]){
        wrongAttempts ++;
      }
    }
    if(wrongAttempts = 0){
      digitalWrite(ledRed, 255);
    }
  }

}
