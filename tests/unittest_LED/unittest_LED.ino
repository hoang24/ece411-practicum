int redLED = 4;

void setup() {
  pinMode(redLED, OUTPUT);
}

void loop() {
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  delay(500);
}
