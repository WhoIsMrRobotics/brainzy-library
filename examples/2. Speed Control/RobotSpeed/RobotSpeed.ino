/*
 * RobotSpeed
 * This example shows how to control the speed of your robot.
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
  Robby.setMode(DIFFERENTIAL); // initialize robot mode : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.noSlaved();            // no slaved robot = speed control
  
  Robby.speedWrite(150, 0, 0);
    // Three arguments :
    //  1. Linear velocity
    //  2. Angular velocity
    //  3. Direction of moving (only for OMNIDIRECTIONAL mode)
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}