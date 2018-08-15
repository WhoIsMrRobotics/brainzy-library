/*
 * Motor
 * This example shows how to set a DC motor speed.
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

void setup() {
  pinMode(MOT1_1, OUTPUT);
  pinMode(MOT1_2, OUTPUT);
}

void loop() {
  setMotorLeftSpeed(150);
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