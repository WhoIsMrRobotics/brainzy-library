/*
 * SimpleAction
 * This example shows how to use simple functions to move your robot.
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
  Robby.setMode(OMNIDIRECTIONAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.slaved();                 // slaved robot = position control

  Robby.turn(90);           // turn 90° from its current position
  //Robby.pointTo(0);       // turn to 90° (absolute coordinate)
  //Robby.translate(-100);  // move backward to 100mm from its current position
  //Robby.goTo(500,500);    // go to the coordinates X=500mm and Y=500mm (only for omnidirectional mode)
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}