//EXERCISE 1: Blink. On for .1 second, off for 1 second
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(100); // milliseconds
  digitalWrite(ledPin, LOW);
  delay(1000);
}
