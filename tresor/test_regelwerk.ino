int data[] = [0,0,0,0,0,0,0,0]

int sh = 11
int st = 12
int ds = 13

void setup(){
    pinMode(sh, OUTPUT);
    pinMode(st, OUTPUT);
    pinMode(sd, OUTPUT);
    
}

void loop(){
  
  for (int index = 0; index <= 7; index ++){
    digitalWrite(ds, 0);
    digitalWrite(sh, 0);
    digitalWrite(ds, daten1[index]);
    delay(20);
    digitalWrite(sh, 1);
    delay(20);
  }
  digitalWrite(st, 1);
}
