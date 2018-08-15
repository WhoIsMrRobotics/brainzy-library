/*
 * BlinkWithoutDelay
 * This example shows how to turn on Robby's LEDs, then turn off, repeatedly without blocking functions.
 *
 * Download latest BRAINZY library here:
 *    https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *
 * Visit Documentation page here:
 *    https://www.mr-robotics.com/docs
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */

#include <BRAINZY.h> // include the robot library

unsigned long oldTime = 0;
unsigned long waitTime = 1000; // waiting time (in ms) 

void setup() {
  // put your setup code here, to run once:
  Robby.ledOff();       // turn the button on board off
  Robby.ledButtonOn();  // turn the button led on
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis()-oldTime > waitTime) {
    oldTime = millis();
    if (Robby.isLedOn() == true) {
      Robby.ledOff();       // turn the button on board off
    }
    else {
      Robby.ledOn();        // turn the button on board on
    }
    if (Robby.isLedButtonOn() == true) {
      Robby.ledButtonOff(); // turn the button led off
    }
    else {
      Robby.ledButtonOn();  // turn the button led on
    }
  }
}