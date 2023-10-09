#include <RedBot.h>

RedBotMotors motors;
RedBotEncoder encoder = RedBotEncoder(A4, A5);
const int MOTOR_SPEED = 90;
const int MOTOR_TURNS = 10;
const int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev

const int DIR = 3;
const int STEP = 9;
const int MAX_STEPS = 3000;
const int PUMP = 11;
const int BEAM_BREAK = A0; // works consistently at 15 inches
// if analogRead(BEAM_BREAK) > 100 then beam is definitely connected
// if analogRead(BEAM_BREAK) < 100 then beam is probably broken
// should make it <30 to know for sure it is broken
bool beamHasConnected = false;
const int LIMIT_SWITCH = A1;
const int LEFT_ENCODER = A4;
const int RIGHT_ENCODER = A5;


void setup() {

  Serial.begin(9600);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(PUMP, OUTPUT);
  Serial.println("WAIT FOR BEAM BREAK");
  

}

void loop() {
  // REMEMBER TO CHANGE THIS TO LESS THEN WHEN THE BEAM BREAKS R PROPERLY MOUNTED******
  if (analogRead(BEAM_BREAK > 100)) {
    beamHasConnected=true;
  }
  if (analogRead(BEAM_BREAK) < 30 && beamHasConnected) {
  beamHasConnected = false;
  Serial.println("DELAY FOR USER SAFETY");
  delay(3000);
  Serial.println("START STEPPER");
  int delayTime = 500;
  int steps = 0;
  digitalWrite(DIR, HIGH);
  while (digitalRead(LIMIT_SWITCH) == LOW && steps < MAX_STEPS) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayTime);
    steps++;
  }
  Serial.println("STOP STEPPER");
  delay(500);
  Serial.println("START PUMP");
  digitalWrite(PUMP, HIGH);
  delay(2000);
  Serial.println("STOP PUMP");
  digitalWrite(PUMP, LOW);
  delay(500);

  Serial.println("START STEPPER REVERSE");
  digitalWrite(DIR, LOW);
  while (steps > 0) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayTime);
    steps--;
  }
  Serial.println("STOP STEPPER");
  delay(500);
  Serial.println("START PULLEYS");
  while (encoder.getTicks(RIGHT)<=MOTOR_TURNS*countsPerRev && encoder.getTicks(LEFT)<=MOTOR_TURNS*countsPerRev) {
    motors.rightMotor(MOTOR_SPEED);
    motors.leftMotor(MOTOR_SPEED);
  }
  motors.brake();
  Serial.println("PAUSE PULLEYS");
  encoder.clearEnc(RIGHT);
  encoder.clearEnc(LEFT);
  delay(500);
  Serial.println("REVERSE PULLEYS");
  while (encoder.getTicks(RIGHT)>= -MOTOR_TURNS*countsPerRev && encoder.getTicks(LEFT)>= -MOTOR_TURNS*countsPerRev) {
    motors.rightMotor(-MOTOR_SPEED);
    motors.leftMotor(-MOTOR_SPEED);
  }
  Serial.println("STOP PULLEYS");
  motors.brake();
  encoder.clearEnc(RIGHT);
  encoder.clearEnc(LEFT);
  Serial.println("WAIT FOR BEAM BREAK");

  
  }

  delay(10);

}
