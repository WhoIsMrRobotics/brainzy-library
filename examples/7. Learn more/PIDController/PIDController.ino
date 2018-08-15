/*
 * PIDController
 * This example shows how to control motor position using PID controller.
 *
 * Download latest BRAINZY library here:
 *    https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *
 * Visit Documentation page here:
 *    https://www.mr-robotics.com/docs/pinout
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */
 
#include <BrainzyPinout.h> // cross-reference between the Brainzy pins and their code label

float target = 0.;
volatile long cptencoder = 0L;

float Kp = 1.;
float Ki = 0.;
float Kd = 0.;

float olderror = 0.;
float sumerror = 0.;
unsigned long oldtime = 0L;
unsigned long oldtime_plot = 0L;

void setup() {
  USB.begin(115200);

  pinMode(MOT1_1, OUTPUT);
  pinMode(MOT1_2, OUTPUT);

  pinMode(ENC1_A, INPUT);
  pinMode(ENC1_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC1_A), interruptEncA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_B), interruptEncB, CHANGE);
}

void loop() {
  if (millis()-oldtime > 10UL) {
    noInterrupts();
    float error = target - (float)cptencoder/11.;
    interrupts();
    olderror = error;
    sumerror += error
    oldtime = millis();
    float cmd = Kp*error + Ki*sumerror + Kd*(error - olderror);
    cmd = constrain(cmd, -255., 255.);
    setMotorLeftSpeed((int)cmd);
  }
}


void interruptEncA(void) { //Left encoder chanel A
  noInterrupts();
  if (digitalRead(ENC1_A) == digitalRead(ENC1_B)) cptencoder--;
  else cptencoder++;
  interrupts();
}

void interruptEncB(void) { //Left encoder chanel B
  noInterrupts();
  if (digitalRead(ENC1_A) == digitalRead(ENC1_B)) cptencoder++;
  else cptencoder--;
  interrupts();
}

void setMotorLeftSpeed(int s) {
  s = constrain(s, -255, 255);
  if (s > 0) {
    analogWrite(MOT1_1, s);
    analogWrite(MOT1_2, 0);
  }
  else {
    analogWrite(MOT1_1, 0);
    analogWrite(MOT1_2, -s);
  }
}