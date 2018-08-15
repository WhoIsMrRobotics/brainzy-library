/*
 * MultiActionsWithoutDelay
 * This example shows how to run multi sequential actions on Robby without blocking functions.
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

int transition = 0;

void setup() {
  // put your setup code here, to run once:
  Robby.setMode(DIFFERENTIAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.slaved();              // slaved robot = position control

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Robby.isActionDone() && transition==0) action0();
  if (Robby.isActionDone() && transition==1) action1();
  if (Robby.isActionDone() && transition==2) action2();
}

void action0() {
  Robby.translate(100); // move forward to 100mm from its current position
  transition=1;
}

void action1() {
  Robby.turn(90); // turn 90° from its current position
  transition=2;
}

void action2() {
  Robby.stop(); // stop Robby
}