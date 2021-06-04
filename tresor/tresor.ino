#include <Console.h>;
#include <LiquidCrystal.h>

// Arduino-Pin verbunden mit SH_CP des 74HC595
int shiftPin = 11;
// Arduino-Pin verbunden mit ST_CP des 74HC595
int storePin = 12;
// Arduino-Pin verbunden mit DS des 74HC595
int dataPin = 13;

int eingabeCode[4];

int adminCode[4] = {1,2,3,4};

int ledGreen;
int ledRed;

int taster2;
int taster3;
int taster4;
int taster5;
int tasterReset;

int index = 0;

const int rs = 1, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

 //Serial.begin(9600);
  
 pinMode(storePin, OUTPUT);
 pinMode(shiftPin, OUTPUT);
 pinMode(dataPin, OUTPUT);

 pinMode(2, INPUT);
 pinMode(3, INPUT);
 pinMode(4, INPUT);
 pinMode(5, INPUT);
 
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);

 pinMode(A0, INPUT);
 // pinMode(A5, OUTPUT);

 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 // Print a message to the LCD.
 lcd.print("Pin eingeben:");

}
 
void loop () {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(1, 0);
  // print the number of seconds since reset:
  
  


  
  taster2 = digitalRead(2);
  taster3 = digitalRead(3);
  taster4 = digitalRead(4);
  taster5 = digitalRead(5);
  tasterReset = digitalRead(0);

  digitalWrite(11 ,LOW);
  digitalWrite(12 ,LOW);

  if (taster2 == LOW){
    delay(800);
    eingabeCode[index] = 1;
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("1");
  } else {
  }

  if (taster3 == LOW){
    delay(800);
    eingabeCode[index] = 2;
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("2");
  } else {
  }

  if (taster4 == LOW){
    delay(800);
    eingabeCode[index] = 3;
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("3");
  } else {
  }

  if (taster5 == LOW){
    delay(800);
    eingabeCode[index] = 4;
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("4");
  } else {
  }

  if (tasterReset == LOW){
    delay(800);
    for (int i = 0; i<4; i++){
      // lcd.setCursor(i, 1);
      // lcd.print(" ");
      eingabeCode[i] = 0;
    }
    lcd.clear();
    lcd.print("Pin eingeben:");
    index = 0;
    tone(A5, 1000);
    delay(1000);
    noTone(A5);
  } else {
  }

  if(index == 4){
      if(
        eingabeCode[0] == adminCode[0] && 
        eingabeCode[1] == adminCode[1] && 
        eingabeCode[2] == adminCode[2] &&
        eingabeCode[3] == adminCode[3]
      ){
        digitalWrite(12, HIGH);
        lcd.clear();
        lcd.print("Entsperrt");
        delay(200);
        // tone(A5, 1000);
        // delay(2000);
        // noTone(A5);
      }
      else {
        digitalWrite(11, HIGH);
        lcd.clear();
        lcd.print("Falscher Pin");
        delay(200);
      }
  }



}
