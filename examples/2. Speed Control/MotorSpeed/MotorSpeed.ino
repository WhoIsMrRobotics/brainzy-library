/*
 * MotorSpeed
 * This example shows how to control the speed of each motors.
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
  Robby.setMode(DIFFERENTIAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.noSlaved();            // no slaved robot = speed control

  // motor speed is determined by PWM input (from -255 to 255)
  Robby.leftMotorWrite(150);
  Robby.rightMotorWrite(-150);
  //Robby.frontMotorWrite(150);	// only for OMNIDIRECTIONAL mode
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}