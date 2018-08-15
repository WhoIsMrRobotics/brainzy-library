/*
 * Scanner
 * This example shows how scanning Widget addresses.
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

void setup() {
  Widgets.begin();

  SerialUSB.begin(115200);  // start USB communication (115200 bauds)
  SerialUSB.println("Widget Scanner\n");
}


void loop() {
  byte error, address;
  int nDevices;

  SerialUSB.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Widgets.beginTransmission(address);
    error = Widgets.endTransmission();

    if (error == 0) {
      SerialUSB.print("A Widget has found with the I2C address 0x");
      if (address<16) SerialUSB.print("0");
      SerialUSB.println(address,HEX);
      nDevices++;
    }
  }
  if (nDevices == 0) SerialUSB.println("No widget found !\n");
  else SerialUSB.println("done\n");

  delay(5000);
}