/*
  Michael Schädler
  Kay Wild
  Mattia Müggler
  
  Version: 1.1
*/

#include <LiquidCrystal.h>

int eingabeCode[4];
int setzeCode[4];

int ledRot; // Pin 11
int ledGruen; // Pin 12

// Zahl == digitaler Port
int taster2;
int taster3;
int taster4;
int taster5;
int tasterZuruecksetzen;
int tasterSet;

// Displayports
const int rs = 1,
  en = 6,
  d4 = 7,
  d5 = 8,
  d6 = 9,
  d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int anzPinFehler = 0; // zählt anzahl Fehleingaben
int setzePinStart = 0; // Überprüft auf erstbenützung --> 0 == erstBenutzung | 1 == schonBenutzt
int index = 0; // für Pin-Array
int setzePin = 0; // ob neuer Pin setztbar --> 0 == nein | 1 == ja
int tuereStatus = 0; // Status des Tresors --> 0 == geschlossen | 1 == geöffnet

void setup() {

  pinMode(0, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(13, INPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(A0, INPUT);

  lcd.begin(16, 2);
  lcd.print("Pin eingeben:");

  // Rotes LED leuchtet standardmässig und grünes LED ist ausgeschaltet
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);

}

void loop() {

  lcd.setCursor(1, 0);

  // Taster-Pins werden festgelegt
  taster2 = digitalRead(2);
  taster3 = digitalRead(3);
  taster4 = digitalRead(4);
  taster5 = digitalRead(5);
  tasterZuruecksetzen = digitalRead(0);
  tasterSet = digitalRead(13);

  // Bei Neustart: Pin setzen
  if (setzePinStart == 0) {
    setzePin = 1;
    setzePinStart = 1;
    lcd.setCursor(0, 0);
    lcd.print("Setze neuer Pin:");
    delay(200);
  }

  // Bei geschlossener Türe: LEDs konfigurieren
  if (tuereStatus == 0) {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  } else {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
  }

  // Prüft die Anzahl der Falscheingaben
  if (anzPinFehler >= 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("zum oeffnen ");
    lcd.setCursor(0, 1);
    lcd.print("an das Personal");

    tone(A5, 1000);
    digitalWrite(11, HIGH);
    delay(300);
    noTone(A5);
    digitalWrite(11, LOW);
    delay(300);
    tone(A5, 1000);
    digitalWrite(11, HIGH);
    delay(300);
    noTone(A5);
    digitalWrite(11, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("an das Personal");
    lcd.setCursor(0, 1);
    lcd.print("wenden");
    delay(300);
  }

  // setzt die Zahl 1 zum Pin
  if (taster2 == LOW) {
    delay(800);
    if (setzePin == 0) {
      eingabeCode[index] = 1;
    } else {
      setzeCode[index] = 1;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print(1);
  }

  // setzt die Zahl 2 zum Pin
  if (taster3 == LOW) {
    delay(800);
    if (setzePin == 0) {
      eingabeCode[index] = 2;
    } else {
      setzeCode[index] = 2;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 2);
    lcd.print(2);
  }

  // setzt die Zahl 3 zum Pin
  if (taster4 == LOW) {
    delay(800);
    if (setzePin == 0) {
      eingabeCode[index] = 3;
    } else {
      setzeCode[index] = 3;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 3);
    lcd.print(3);
  }

  // setzt die Zahl 4 zum Pin
  if (taster5 == LOW) {
    delay(800);
    if (setzePin == 0) {
      eingabeCode[index] = 4;
    } else {
      setzeCode[index] = 4;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 4);
    lcd.print(4);
  }

  // löscht die Eingabe
  if (tasterZuruecksetzen == LOW) {
    delay(800);

    if (setzePin == 0) {
      eingabeCode[index] = 4;
    } else {
      setzeCode[index] = 4;
    }

    if (index > 0) {
      index -= 1;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pin eingeben:");
    for (int i = 0; i < index; i++) {
      int zeileCursor = i + 1;
      lcd.setCursor(zeileCursor, 1);
      lcd.print(eingabeCode[i]);
    }
    tuereStatus = 0;
    tone(A5, 1000);
    delay(1000);
    noTone(A5);
  }

  // Setzt den Modus, um einen Pin zu erstellen
  if (tasterSet == LOW) {
    if (tuereStatus == 1) {
      //tone(A5, 1000);
      //delay(500);
      //noTone(A5);
      lcd.clear();
      lcd.print("Setze Pin:");
      setzePin = 1;
    } else {
      lcd.clear();
      lcd.print("zuerst oeffnen");
      delay(2000);
      index = 0;
      lcd.clear();
      lcd.print("Pin eingeben:");
    }
  }

  // Überprüft die Eingabe
  // Überprüft nach 4 Zeichen, ob es der richtige Code war
  if (index == 4) {
    if (setzePin == 0) {
      if (
        eingabeCode[0] == setzeCode[0] &&
        eingabeCode[1] == setzeCode[1] &&
        eingabeCode[2] == setzeCode[2] &&
        eingabeCode[3] == setzeCode[3]
      ) {
        index = 0;
        setzePinStart = 1;
        tuereStatus = 1;
        anzPinFehler = 0;
        setzePinStart = 1;
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        lcd.clear();
        lcd.print("Entsperrt");
        delay(200);
      } else {
        index = 0;
        tuereStatus = 0;
        anzPinFehler += 1;
        digitalWrite(11, LOW);
        delay(200);
        digitalWrite(11, HIGH);
        delay(200);
        lcd.clear();
        lcd.print("Falscher Pin");
        delay(2000);
        lcd.clear();
        lcd.print("Pin eingeben:");
        delay(200);
      }
    }
  } else if (setzePin == 1) {
    setzePin = 0;
    index = 0;
    digitalWrite(12, HIGH);
    lcd.clear();
    lcd.print("neuer Pin gesetzt");
    for (int i = 0; i < 4; i++) {
      lcd.setCursor(i, 1);
      lcd.print(setzeCode[i]);
    }
    delay(2000);
    lcd.clear();
    lcd.print("druecke Reset");
  }

}
