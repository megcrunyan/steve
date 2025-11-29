# include "IRremote.h"

// Define motor pins
const int motorAPin1=7;
const int motorAPin2=8;
const int motorBPin1=9;
const int motorBPin2=10;
const int ENAPin=5;
const int ENBPin=6;

// Define IR remote pin + vars
const int IRReceivePin=12;
int direction = 0;
int command;
unsigned long last_input;

// Define IR Sensor Pins + vars
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
bool calibrated;
struct setPoint {
  public:
  int IR1;
  int IR2;
  int IR3;
  int IR4;
  int IR5;
};
setPoint p;
int on;
int scaleFactor[5] = {-2, -1, 0, 1, 2};
int error[5] = {0, 0, 0, 0, 0};
int cumulative_error = 0;
int correction;
int prev_err = 0;
int kp = 1;
int ki = 0;
int kd = 0;
unsigned long last_line;
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
  // set up line following mode
  calibrated = false;
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
      }
      else{
        keep_going(command);
      }
      IrReceiver.resume();
    }
    last_input = millis();
    }
  if(millis() - last_input > 750) {
    friction_brake();
  }
}

void go_backward(){
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}

void go_forward(){
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorBPin1, LOW);
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
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}

void turn_right(){
  analogWrite(ENAPin, speedMode2);
  analogWrite(ENBPin, speedMode1);
}

void turn_left(){
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode2);
}

void spin_right(){
  digitalWrite(motorBPin2, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}

void spin_left(){
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(ENAPin, speedMode1);
  analogWrite(ENBPin, speedMode1);
}
void line_following(){
  if (!calibrated){
  p = {
    analogRead(IRPin1), 
    analogRead(IRPin2), 
    analogRead(IRPin3), 
    analogRead(IRPin4),
    analogRead(IRPin5)
    };
    calibrated = true;
  }

  go_forward();
  on = p.IR3 + 100;  // Adding tolerance in case of shadows
  IR1 = analogRead(IRPin1); 
  IR2 = analogRead(IRPin2);
  IR3 = analogRead(IRPin3);
  IR4 = analogRead(IRPin4);
  IR5 = analogRead(IRPin5);
  
  if (IR1 < on){
    error[0] = (IR1 - p.IR1)*scaleFactor[0];
    cumulative_error += error[0]/5;
    last_line = millis();
  }
  if (IR2 < on){
    error[1] = (IR2 - p.IR2)*scaleFactor[1];
    cumulative_error += error[1]/5;
    last_line = millis();
  }
  if (IR3 < on){
    error[2] = (IR3 - p.IR3)*scaleFactor[2];
    cumulative_error += error[2]/5;
    last_line = millis();
  }
  if (IR4 < on){
    error[3] = (IR4 - p.IR4)*scaleFactor[3];
    cumulative_error += error[3]/5;
    last_line = millis();
  }
  if (IR5 < on){
    error[4] = (IR5 - p.IR5)*scaleFactor[4];
    cumulative_error += error[4]/5;
    last_line = millis();
  }
  int err_sum = 0;
  for (int i = 0; i < sizeof(error); i++){
    err_sum += error[i];
  } 
  correction = kp*err_sum + ki*cumulative_error + kd*(err_sum - prev_err);
  prev_err = err_sum;
  if (correction < 0){
    correction = correction * -1;
    if (correction > speedMode1){ //keep from an invalid value
      correction = 0;
    }
    analogWrite(ENAPin, speedMode1);
    analogWrite(ENBPin, correction);
  }
  if (correction > 0){
    if (correction > speedMode1){
      correction = 0;
    }
    analogWrite(ENAPin, correction);
    analogWrite(ENBPin, speedMode1);
  }
  if ((IR1 > on) & (IR2 > on) & (IR3 > on) & (IR4 > on) & (IR5 > on)){
    go_forward();
    if(millis() - last_line > 3000) {
    friction_brake();
    } 
  }
}

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

