/*
 * ConfigWifi
 * This example shows how to configure a Wifi communication using AT commands in the Serial Monitor.
 * Make sure you have selected the following setting in the Serial Monitor :
 *    - 'Both NL & CR'
 *    - '115200 baud'
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

bool isSent = true;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);  // start USB communication (115200 bauds)
  SerialWifi.begin(115200); // start Wifi communication (115200 bauds)
  
  SerialUSB.println("Communication is ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  // read from USB, send to Wifi
  while(SerialUSB.available()) {
    if (isSent) {
      SerialUSB.print("-\nYour message: ");
      isSent = false;
    }
    char byteSent = SerialUSB.read();
    SerialWifi.print(byteSent);
    SerialUSB.print(byteSent);
  }

  // read from Wifi, send to USB
  while(SerialWifi.available()) {
    if (!isSent) {
      SerialUSB.println("Your response:");
      isSent = true;
    }
    char byteRecieved = SerialWifi.read();
    SerialUSB.print(byteRecieved);
  }
}