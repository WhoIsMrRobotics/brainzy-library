/*
 * MultiActions
 * This example shows how to run multi sequential actions on Robby.
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
  Robby.slaved();              // slaved robot = position control

}

void loop() {
  // put your main code here, to run repeatedly:
  Robby.translate(100);   // move forward to 100mm from its current position
  Robby.waitActionDone(); // wait for action finish before continuing
  Robby.turn(90);         // turn 90° from its current position
  Robby.waitActionDone(); // wait for action finish before continuing
  Robby.stop();           // stop Robby
  
  while(1);               // infinity loop
}