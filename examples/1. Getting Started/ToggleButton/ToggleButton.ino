/*
 * ToggleButton
 * This example shows how to use the button to turn on/off a Robby's LED.
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

void setup() {
  // put your setup code here, to run once:
  Robby.ledButtonOff(); // turn the button led off
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Robby.isButtonPressed() == true) {
    if (Robby.isLedButtonOn() == true) {
      Robby.ledButtonOff(); // turn the button led off
    }
    else {
      Robby.ledButtonOn();  // turn the button led on
    }
  }
}