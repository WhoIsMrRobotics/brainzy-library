/*
 * AvoidObstacles
 * This example shows how to run multi sequential actions and stop Robby when obstacles are detected.
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
#include <Widgets.h> // include the widgets library

WidgetSonar mySonar(WIDGET_PORT_6); // create a Sonar widget connected to the first port

void setup() {
  // put your setup code here, to run once:
  Widgets.begin();                // initialize widgets communication
  Robby.setMode(OMNIDIRECTIONAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.slaved();                 // slaved robot = position control
}

void loop() {
  // put your main code here, to run repeatedly:
  Robby.translate(100);                // move forward to 100mm from its current position
  Robby.waitActionDone(checkDistance); // wait for action finish before continuing
  Robby.turn(90);                      // turn 90° from its current position
  Robby.waitActionDone();              // wait for action finish before continuing
  Robby.stop();                        // stop Robby
  
  while(1);                            // infinite loop
}

void checkDistance() {
  float distance = mySonar.distanceRead(); // read the distance to an obstacle
  if (distance < 10) Robby.stop();         // stop Robby when an obstacle is too close
}
