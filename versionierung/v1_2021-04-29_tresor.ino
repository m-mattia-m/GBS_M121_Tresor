/*
 * Settings: (Digital-Input)
 * Btn 1 : 1
 * Btn 2 : 2
 * Btn 3 : 3
 * Btn 4 : 4
 * Btn S : 6
 * Btn C : 7
 * Piezo : 9
 * LED R : 11
 * LED G : 12
 * 
 * 6 Input | 3 Output
*/

int code = 1234;
int countFalseCode = 0;
int tempCode;

int btn1 = 1;
int btn2 = 2;
int btn3 = 3;
int btn4 = 4;
int btnS = 6;
int btnC = 7;
int piezo = 9;
int ledR = 11;
int ledG = 12;

int val1 = 1;
int val2 = 2;
int val3 = 3;
int val4 = 4;

void setup(){
    pinMode(btn1, INPUT);
    pinMode(btn2, INPUT);
    pinMode(btn3, INPUT);
    pinMode(btn4, INPUT);
    pinMode(btnS, INPUT);
    pinMode(btnC, INPUT);
    pinMode(piezo, OUTPUT);
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
}

void loop(){
  if(digitalRead(btn1)){
    digitalWrite(ledG, HIGH)
  }
  if(digitalRead(btn2)){
    digitalWrite(ledR, HIGH)
  }

  
}
