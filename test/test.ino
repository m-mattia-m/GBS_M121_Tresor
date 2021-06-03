void setup() {
  pinMode(3, OUTPUT);
  pinMode(A5, OUTPUT);
  
}

void loop() {
  //digitalWrite(3, HIGH); 
  tone(A5, 1000);
  delay(1000);
  noTone(A5);
  delay(10000);
  
}
