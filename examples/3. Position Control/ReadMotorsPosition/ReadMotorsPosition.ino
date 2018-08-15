/*
 * ReadMotorsPosition
 * This example shows how to get and display motors position.
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

// global variables to save positions
float angleMotLeft = 0;
float angleMotRight = 0;
float angleMotFront = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);        // start USB communication
  Robby.setMode(OMNIDIRECTIONAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Robby.isButtonPressed() == true) {
    Robby.resetWheelAngularPositions(); // reset motors position when button is pressed.
  }
  
  angleMotLeft = Robby.leftMotorPositionRead();
  angleMotRight = Robby.rightMotorPositionRead();
  angleMotFront = Robby.frontMotorPositionRead();
  
  SerialUSB.println("-------------------");
  SerialUSB.println("MOTORS POSITION\n");
  SerialUSB.print("Left motor: ");
  SerialUSB.print(angleMotLeft);
  SerialUSB.print(" deg\nRight motor: ");
  SerialUSB.print(angleMotRight);
  SerialUSB.print(" deg\nFront motor: ");
  SerialUSB.print(angleMotFront);
  SerialUSB.println(" deg\n");

  delay(3000);
}