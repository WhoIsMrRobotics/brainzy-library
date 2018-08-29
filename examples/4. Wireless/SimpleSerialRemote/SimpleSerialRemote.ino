/*
 * SimpleSerialRemote
 * This example shows how to use very simple commands from the Serial Monitor to remote Robby.
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

#define serial SerialBluetooth  // serial port (for example: SerialUSB or SerialBluetooth)

float distance = 0;
float angle = 0;

void setup() {
  serial.begin(9600);        // start serial communication (9600 bauds)
  Robby.setMode(DIFFERENTIAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.slaved();              // slaved robot = position control
}

void loop() {
  if (serial.available()>0 && Robby.isActionDone()) {
    switch(serial.read()) {
      case 'S':
        Robby.stop();
        break;
      case 'M': 
        distance = serial.parseFloat();
        Robby.translate(distance);
        break;
      case 'T':
        angle = serial.parseFloat();
        Robby.turn(angle);
        break;
    }
  }
}