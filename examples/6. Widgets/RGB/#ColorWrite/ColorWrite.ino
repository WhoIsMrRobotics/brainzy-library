/*
 * ColorWrite
 * This example shows how to control the RGB widget color.
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

WidgetRGB myRGB(WIDGET_PORT_1); // declare a RGB widget on the first port

void setup() {
  // put your setup code here, to run once:
  Widgets.begin();
  myRGB.colorWrite(255,0,0); // set the RGB widget color in red
  delay(100);
  myRGB.colorWrite(0,255,0); // set the RGB widget color in green
  delay(100);
  myRGB.colorWrite(0,0,255); // set the RGB widget color in blue
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}