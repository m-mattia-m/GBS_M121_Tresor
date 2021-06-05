#include <Console.h>;

#include <LiquidCrystal.h>

int eingabeCode[4];

int setCode[4];

int adminCode[4] = {
  1,
  2,
  3,
  4
};

int ledRed; // Pin 11
int ledGreen; // Pin 12

int taster2;
int taster3;
int taster4;
int taster5;
int tasterReset;
int tasterSet;
int countPinErrors = 0;

int index = 0;
int setPin = 0;
int tuereStatus = 0;

const int rs = 1,
  en = 6,
  d4 = 7,
  d5 = 8,
  d6 = 9,
  d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Pin eingeben:");

}

void loop() {

  lcd.setCursor(1, 0);

  taster2 = digitalRead(2);
  taster3 = digitalRead(3);
  taster4 = digitalRead(4);
  taster5 = digitalRead(5);
  tasterReset = digitalRead(0);
  tasterSet = digitalRead(13);

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  
  // Prüft die anzahl der Falscheingaben
  if (countPinErrors >= 3){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("zum oeffnen ");
    lcd.setCursor(0,1);
    lcd.print("an das Personal");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("an das Personal");
    lcd.setCursor(0,1);
    lcd.print("wenden");
    delay(2000);
  }

  // setzt die zahl 1 zum Pin
  if (taster2 == LOW) {
    delay(800);
    if (setPin == 0) {
      eingabeCode[index] = 1;
    } else {
      setCode[index] = 1;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("1");
  } else {}

  // setzt die zahl 2 zum Pin
  if (taster3 == LOW) {
    delay(800);
    if (setPin == 0) {
      eingabeCode[index] = 2;
    } else {
      setCode[index] = 2;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("2");
  } else {}

  // setzt die zahl 3 zum Pin
  if (taster4 == LOW) {
    delay(800);
    if (setPin == 0) {
      eingabeCode[index] = 3;
    } else {
      setCode[index] = 3;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("3");
  } else {}

  // setzt die zahl 4 zum Pin
  if (taster5 == LOW) {
    delay(800);
    if (setPin == 0) {
      eingabeCode[index] = 4;
    } else {
      setCode[index] = 4;
    }
    index++;
    tone(A5, 1000);
    delay(100);
    noTone(A5);
    lcd.setCursor(index, 1);
    lcd.print("4");
  } else {}

  // löscht die Eingabe
  if (tasterReset == LOW) {
    delay(800);
    for (int i = 0; i < 4; i++) {
      // lcd.setCursor(i, 1);
      // lcd.print(" ");
      eingabeCode[i] = 0;
    }
    lcd.clear();
    lcd.print("Pin eingeben:");
    index = 0;
    tuereStatus = 0;
    tone(A5, 1000);
    delay(1000);
    noTone(A5);
  } else {}

  // setzt den Modus um einen Pin zu erstellen
  if (tasterSet == LOW) {
    if (tuereStatus == 1) {
      tone(A5, 1000);
      delay(500);
      noTone(A5);
      lcd.clear();
      lcd.print("Setze Pin:");
      setPin = 1;
    } else {
      lcd.clear();
      lcd.print("zuerst oeffnen");
      delay(2000);
      index = 0;
      lcd.clear();
      lcd.print("Pin eingeben:");
    }
  }

  // Überprüft nach 4 zeichen ob es der richtige code war
  if (index == 4) {
    if (setPin == 0) {
      if (
        (
          eingabeCode[0] == setCode[0] &&
          eingabeCode[1] == setCode[1] &&
          eingabeCode[2] == setCode[2] &&
          eingabeCode[3] == setCode[3]
        ) ||
        (
          eingabeCode[0] == adminCode[0] &&
          eingabeCode[1] == adminCode[1] &&
          eingabeCode[2] == adminCode[2] &&
          eingabeCode[3] == adminCode[3]
        )
      ) {
        index = 0;
        tuereStatus = 1;
        countPinErrors = 0;
        digitalWrite(12, HIGH);
        lcd.clear();
        lcd.print("Entsperrt");
        delay(200);
      } else {
        index = 0;
        tuereStatus = 0;
        countPinErrors += 1;
        digitalWrite(11, HIGH);
        lcd.clear();
        lcd.print("Falscher Pin");
        delay(2000);
        lcd.clear();
        lcd.print("Pin eingaben:");
        delay(200);
      }
    } else if (setPin == 1) {
      setPin = 0;
      index = 0;
      digitalWrite(12, HIGH);
      lcd.clear();
      lcd.print("neuer Pin gesetzt");
      for (int i = 0; i < 4; i++) {
        lcd.setCursor(i, 1);
        lcd.print(setCode[i]);
      }
      delay(2000);
      lcd.clear();
      lcd.print("druecke Reset");
    }
  }

}
