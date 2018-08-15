/*
 * AndroidRemote
 * This example shows how to control Robby over SerialBluetooth using your Android.
 * 
 * Download the Android App on PlayStore:
 *    https://play.google.com/store/apps/details?id=org.projectproto.btjoystick
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

void setup()  {
  // put your setup code here, to run once:
  Robby.setMode(DIFFERENTIAL);    // initialize the Robot : DIFFERENTIAL or OMNIDIRECTIONAL
  Robby.noSlaved();               // set the control mode > speed control
  
  SerialUSB.begin(9600);          // starts SerialUSB communication (9600 bauds)
  SerialBluetooth.begin(9600);    // starts SerialBluetooth communication (9600 bauds)
  
  while(SerialBluetooth.available()) SerialBluetooth.read(); // empty RX buffer
}

void loop() {
  // put your main code here, to run repeatedly:
  // receive and send data from smartphone
  receivedSerialBluetoothData();
  sendSerialBluetoothData(); 
}
