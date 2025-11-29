# include "IRremote.h"

// Define motor pins
const int motorAPin1=7;
const int motorAPin2=8;
const int motorBPin1=9;
const int motorBPin2=10;
const int ENAPin=5;
const int ENBPin=6;

// Define IR remote pin
const int IRReceivePin=12;
int direction = 0;
int command;
unsigned long last_input;

// Define IR Sensor Pins
// From back left to right
const int IRPin1 = A0;
const int IRPin2 = A1;
const int IRPin3 = A2;
const int IRPin4 = A3;
const int IRPin5 = A4;
int IR1;
int IR2;
int IR3;
int IR4;
int IR5;

// Define Speed Modes
int speedMode1 = 128;
int speedMode2 = 48;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRReceivePin, ENABLE_LED_FEEDBACK);
  // Left Motor
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(ENAPin, OUTPUT);
  // Right Motor
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(ENBPin, OUTPUT);
  // start stopped
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}

void loop() {
  if (IrReceiver.decode()){
    if(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT){
      keep_going(command);
      IrReceiver.resume();
    }
    else{
      command = IrReceiver.decodedIRData.command;
      Serial.println(command);
      if(command == 68){ 
        line_following();
      else:
        keep_going(command);
      IrReceiver.resume();
    }
    last_input = millis();
    }
  if(millis() - last_input > 1000) {
    friction_brake();
  }
}

void go_backward(){
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin2, LOW);
  delay(100);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}

void go_forward(){
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorBPin1, LOW);
  delay(100);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}

void friction_brake(){
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}

void electrical_brake(){
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, HIGH);
  delay(100);
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}

void turn_left(){
  analogWrite(ENAPin, speedMode2);
  analogWrite(ENBPin, speedMode1);
}

void turn_right(){
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode2);
}

void spin_left(){
  digitalWrite(motorBPin2, LOW);
  digitalWrite(motorAPin2, LOW);
  delay(100);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}

void spin_right(){
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  delay(100);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}
void line_following(){
  speedMode1 = 70;
  speedMode2 = 30;
  IR1 = analogRead(IRPin1);
  IR2 = analogRead(IRPin2);
  IR3 = analogRead(IRPin3);
  IR4 = analogRead(IRPin4);
  IR5 = analogRead(IRPin5);


void keep_going(int command){
  switch (command){
      case 69: // 1, Slow
        speedMode1 = 128;
        speedMode2 = 48;
        break;
      case 70: // 2, Fast
        speedMode1 = 255;
        speedMode2 = 128;
        break;
      case 24: // Up arrow, Forward
        go_forward();
        direction = 1;
        break;
      case 82: // Down arrow
        go_backward();
        direction = 2;
        break;
      case 90: // Right arrow
        if(direction == 0){
          // define default as forward if hit from stopped
          go_forward();
          direction = 1;
          turn_right();
        }
        else {
          turn_right();
        }
        break;
      case 8: // Left arrow
        if (direction == 0){
          // Define default as forward if hit from stopped
          go_forward();
          direction = 1;
          turn_left();
        }
        else {
          turn_left();
        }
        break;
      case 13: // Octothorpe
        spin_right();
        direction = 0;
        break;
      case 22: // Asterisk
        spin_left();
        direction = 0;
        break;
      case 28: // OK
        electrical_brake();
        direction = 0;
        break;
      default: 
        friction_brake();
        direction = 0;
        break;
    }
  }