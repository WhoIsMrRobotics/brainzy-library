/*
 * ConfigBluetooth
 * This example shows how to configure a Bluetooth communication using AT commands in the Serial Monitor.
 * Make sure the Brainzy board AT-MODE is turn on and you have selected the following setting in the Serial Monitor :
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
  SerialUSB.begin(115200);      // start USB communication (115200 bauds)
  SerialBluetooth.begin(38400); // start BT communication (38400 bauds)
  
  SerialUSB.println("Communication with Bluetooth module is ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  // read from USB, send to Bluetooth
  while(SerialUSB.available()) {
    if (isSent) {
      SerialUSB.print("-\nYour message: ");
      isSent = false;
    }
    char byteSent = SerialUSB.read();
    SerialBluetooth.print(byteSent);
    SerialUSB.print(byteSent);
  }

  // read from Bluetooth, send to USB
  while(SerialBluetooth.available()) {
    if (!isSent) {
      SerialUSB.println("Your response:");
      isSent = true;
    }
    char byteRecieved = SerialBluetooth.read();
    SerialUSB.print(byteRecieved);
  }
}