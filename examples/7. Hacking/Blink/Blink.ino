/*
 * Blink
 * This example shows how blinking the led buildin.
 *
 * Download latest BRAINZY library here:
 *		https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *
 * Visit Documentation page here:
 *		https://www.mr-robotics.com/docs/pinout
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */
 
#include <BrainzyPinout.h> // cross-reference between the Brainzy pins and their code label
#define myLed BUILTIN_LED

unsigned long duration = 1000UL;
bool state = false;
unsigned long oldTime = 0L;

void setup() {
  pinMode(myLed, OUTPUT);
}

void loop() {
  if (millis() - oldTime > duration) {
    oldTime = millis();
    state = !state;
    digitalWrite(myLed, state);
  }
}