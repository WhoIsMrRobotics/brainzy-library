/*
 * RobotName
 * This example shows how to give a name to your robot. It will be saved in his EEPROM memory.
 * 
 * Download latest BRAINZY library here:
 *    https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *
 * Visit Documentation page here:
 *    https://www.mr-robotics.com/docs
 *	  https://www.arduino.cc/en/Reference/EEPROM
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */
 
#include <BRAINZY.h> // include the robot library

char container[8]; // your name can only be composed with 8 char

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);      // starts USB communication
  Robby.nameWrite("My Robby");  // write a robot name (with 8 letters max)
  Robby.nameRead(container);    // read and save the name in 'container'
  SerialUSB.println(container); // display it on the serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}