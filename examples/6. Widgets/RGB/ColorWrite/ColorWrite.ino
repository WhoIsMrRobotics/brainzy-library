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
  Widgets.begin();      // initialize widgets communication
  myRGB.clear();        // turn off all pixels
  myRGB.brightness(10); // adjust the brightness level of all pixels from 0 to 255
  
  // check if myRGB is correctly connected
  if (!myRGB.isConnected()) {
    SerialUSB.println("Error: myRGB is not connected.");
    while(1); // infinite loop
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int k = 0; k < myRGB.size(); k += 1) {
    // colorWrite sends the updated k-pixel color to the widgets
    // you need to specify RGB values from 0,0,0 up to 255,255,255
    // if K is not specify, all pixel will be updated
    myRGB.colorWrite(255, 0, 0, k);
    delay(100);
  }
  
  for (int k = 0; k < myRGB.size(); k += 2) {
    myRGB.colorWrite(0, 255, 0, k);
    delay(100);
  }
  
  for (int k = 0; k < myRGB.size(); k += 3) {
    myRGB.colorWrite(0, 0, 255, k);
    delay(100);
  }

  myRGB.clear(); // turn off all pixels
}