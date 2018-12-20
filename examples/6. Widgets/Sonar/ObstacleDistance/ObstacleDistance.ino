/*
 * ObstacleDistance
 * This example shows how to detect obstacles using a Sonar Widget.
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

WidgetSonar mySonar(WIDGET_PORT_1); // create a Sonar widget connected to the first port

void setup() {
  // put your setup code here, to run once:
  Widgets.begin();         // initialize widgets communication
  SerialUSB.begin(115200); // start USB communication (115200 bauds)

  // check if mySonar is correctly connected
  if (!mySonar.isConnected()) {
    SerialUSB.println("Error: mySonar is not connected.");
    while(1); // infinite loop
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = mySonar.distanceRead(); // read the distance to an obstacle
  SerialUSB.print(distance);               // display it
  SerialUSB.println(" cm");
  delay(500);
}