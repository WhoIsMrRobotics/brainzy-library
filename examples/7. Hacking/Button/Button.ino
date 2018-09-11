/*
 * Button
 * This example shows how to use a button.
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

void setup() {
  pinMode(BUILTIN_LED_BTN, OUTPUT);
  pinMode(BUILTIN_BTN, INPUT_PULLUP);    
}

void loop() {
  if(!digitalRead(BUILTIN_BTN)) {
  	digitalWrite(BUILTIN_LED_BTN, HIGH);
  	}
  else {
  	digitalWrite(BUILTIN_LED_BTN, LOW);
  	}
}