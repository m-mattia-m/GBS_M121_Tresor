void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  analogWrite(3, 255); 
  Serial.print("Hello world");
}
