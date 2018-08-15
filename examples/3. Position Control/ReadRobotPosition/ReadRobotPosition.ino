/*
 * ReadRobotPosition
 * This example shows how to get and display Robby's coordinates.
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

float Xp = 0;
float Yp = 0;
float Tp = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);     // start USB communication
  Robby.setMode(DIFFERENTIAL); // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.slaved();              // slaved robot = position control

  Robby.turn(90);             // turn 90° from its current position
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Robby.isButtonPressed() == true) {
    // reset robot position when button is pressed.
    Robby.xPositionWrite(0);
    Robby.yPositionWrite(0);
    Robby.angularPositionWrite(0);
  }

  Xp = Robby.xPositionRead();
  Yp = Robby.yPositionRead();
  Tp = Robby.angularPositionRead();
  
  SerialUSB.println("-------------------");
  SerialUSB.println("ROBBY'S COORDINATES\n");
  SerialUSB.print("X = ");
  SerialUSB.print(Xp);
  SerialUSB.print(" mm\nY = ");
  SerialUSB.print(Yp);
  SerialUSB.print(" mm\nTheta = ");
  SerialUSB.print(Tp);
  SerialUSB.println(" deg\n");

  delay(3000);
}