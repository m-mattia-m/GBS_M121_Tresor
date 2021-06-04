#include <Console.h>;
#include <LiquidCrystal.h>

// Arduino-Pin verbunden mit SH_CP des 74HC595
int shiftPin = 11;
// Arduino-Pin verbunden mit ST_CP des 74HC595
int storePin = 12;
// Arduino-Pin verbunden mit DS des 74HC595
int dataPin = 13;

 
// Dieses Muster soll ausgegeben werden
int muster[8] = {1,0,0,0,0,0,0,0}; 
// {1,0,0,0,0,0,0,0} == rot
// {0,0,0,0,0,0,1,0} == grün

int eingabeCode[4];

int adminCode[4] = {1,2,3,4};

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
  tasterReset = analogRead(A0);
  //tasterReset = muster[4];

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
    //muster[0] = 0;
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
    //muster[6] = 0;
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
    //muster[6] = 0;
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
    //muster[6] = 0;
  }

  if (tasterReset == LOW){
    delay(800);
    for (int i = 0; i<4; i++){
      lcd.setCursor(i, 1);
      lcd.print(" ");
      eingabeCode[i] = 0;
    }
    tone(A5, 1000);
    delay(1000);
    noTone(A5);
    lcd.setCursor(4, 1);
    lcd.print("reset");
  } else {
    //muster[6] = 0;
  }

  if(index == 4){
    for(int i = 0; i < 4; i++){
      if(eingabeCode[i] == adminCode[i]){
        //Serial.print("EingabeCode-");
        //Serial.print(i);
        //Serial.print(" ->: ");
        //Serial.print(eingabeCode[i]);
        //Serial.print("\t adminCode-");
        //Serial.print(i);
        //Serial.print(" ->: ");
        //Serial.print(adminCode[i]);
        //Serial.print("\n");
        muster[6] = 1; 
        // tone(A5, 1000);
        // delay(2000);
        // noTone(A5);
      }
    }
  }


// ##############################



// storePin sicherheitshalber auf LOW
 digitalWrite(storePin, LOW); 
 
 for (int i=0; i<8; i++) {
 // Zuerst immer alle 3 Pins auf LOW
 // Aktion passiert bei Wechsel von LOW auf HIGH
 digitalWrite(shiftPin, LOW);
 // Jetzt den Wert der aktuellen Stelle ans Datenpin DS anlegen 
 digitalWrite(dataPin, muster[i]);
 // Dann ShiftPin SHCP von LOW auf HIGH, damit wird der Wert
 // am Datenpin ins Register geschoben. 
 digitalWrite(shiftPin, HIGH);
 }
 
 // Wenn alle 8 Stellen im Register sind, jetzt das StorePin STCP
 // von LOW auf HIGH, damit wird Registerinhalt an Ausgabepins
 // kopiert und der Zustand an den LEDs sichtbar
 
 digitalWrite(storePin, HIGH);

}
