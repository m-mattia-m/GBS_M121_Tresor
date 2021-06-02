#include <Console.h>;

// Arduino-Pin verbunden mit SH_CP des 74HC595
int shiftPin = 11;
// Arduino-Pin verbunden mit ST_CP des 74HC595
int storePin = 12;
// Arduino-Pin verbunden mit DS des 74HC595
int dataPin = 13;
 
// Dieses Muster soll ausgegeben werden
int muster[8] = {0,0,0,0,0,0,0,0}; 
// {1,0,0,0,0,0,0,0} == rot
// {0,0,0,0,0,0,1,0} == grün

int eingabeCode[4];

int adminCode[4] = {1,2,3,4};


int taster2;
int taster3;
int taster4;
int taster5;

void setup() {

 Serial.begin(9600);
  
 pinMode(storePin, OUTPUT);
 pinMode(shiftPin, OUTPUT);
 pinMode(dataPin, OUTPUT);

 pinMode(2, INPUT);
 pinMode(3, INPUT);
 pinMode(4, INPUT);
 pinMode(5, INPUT);
 // pinMode(A5, OUTPUT);
 
}
 
void loop () {
  
  taster2 = digitalRead(2);
  taster3 = digitalRead(3);
  taster4 = digitalRead(4);
  taster5 = digitalRead(5);

  if (taster2 == LOW){
    //muster[0] = 1; 
    eingabeCode[sizeof(eingabeCode)] = 1;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    Serial.println("Aktuelle Taste: 1");
  } else {
    //muster[0] = 0;
  }

  if (taster3 == LOW){
    //muster[6] = 1; 
    eingabeCode[sizeof(eingabeCode)] = 2;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    Serial.println("Aktuelle Taste: 2");
  } else {
    //muster[6] = 0;
  }

  if (taster4 == LOW){
    //muster[6] = 1; 
    eingabeCode[sizeof(eingabeCode)] = 3;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    Serial.println("Aktuelle Taste: 3");
  } else {
    //muster[6] = 0;
  }

  if (taster5 == LOW){
    //muster[6] = 1; 
    eingabeCode[sizeof(eingabeCode)] = 4;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    Serial.println("Aktuelle Taste: 4");
  } else {
    //muster[6] = 0;
  }

  for(int i = 0; i < 4; i++){
    Serial.println("Eingabe i=");
    Serial.println(i);
    Serial.println(eingabeCode[i]);
    if(eingabeCode[i] == adminCode[i]){
      Serial.println(i + ": " + eingabeCode[i]);
      muster[6] = 1; 
      tone(A5, 1000);
      delay(2000);
      noTone(A5);
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
