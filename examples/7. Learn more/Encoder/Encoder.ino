/*
 * Encoder
 * This example shows how to use an encoder.
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

volatile long cptencoder = 0L;

void setup() {
  SerialUSB.begin(115200);
  pinMode(ENC1_A, INPUT);
  pinMode(ENC1_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC1_A), interruptEncA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_B), interruptEncB, CHANGE);
}

void loop() {
  SerialUSB.print("Angular position left motor: ");
  SerialUSB.println(cptencoder);
  delay(1000);
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
