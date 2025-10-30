
const int motorAPin1=7;
const int motorAPin2=8;
const int motorBPin1=9;
const int motorBPin2=10;
const int ENAPin=5;
const int ENBPin=6;
void setup() {
  // Left Motor
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(ENAPin, OUTPUT);
  // Right Motor
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(ENBPin, OUTPUT);
}

void loop() {
  // Go forward 2s, half speed
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, 128);
  analogWrite(ENBPin, 128);
  delay(2000);

  // Stop, go backward 2s half speed
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(ENAPin, 128);
  analogWrite(ENBPin, 128);
  delay(2000);

  // Stop, go left 1s half speed
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, 254);
  analogWrite(ENBPin, 128);
  delay(1000);

  // Transition right 1s half speed
  analogWrite(ENAPin, 128);
  analogWrite(ENBPin, 254);
  delay(1000);

  // stop quickly
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin2, HIGH);

  // stay stopped 10s
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
  delay(10000);

  // Repeat above, full speed
  // Go forward 2s
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, 254);
  analogWrite(ENBPin, 254);
  delay(2000);

  // Stop, go backward 2s half speed
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(ENAPin, 254);
  analogWrite(ENBPin, 254);
  delay(2000);

  // Stop, go left 1s half speed
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, 254);
  analogWrite(ENBPin, 0);
  delay(1000);

  // Transition right 1s half speed
  analogWrite(ENAPin, 0);
  analogWrite(ENBPin, 254);
  delay(1000);

  // stop quickly
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin2, HIGH);

  // stay stopped 10s
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
  delay(10000);
}
