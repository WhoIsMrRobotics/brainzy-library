/*
 * MonitoringBattery
 * This example shows how to display the voltage battery.
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

unsigned long oldTime = 0;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200); // initialize USB communication
}

void loop() {
  // put your main code here, to run repeatedly:
  // Do not use the delay () or other functions with which your program is paused !
  Robby.checkBattProcess(); // Check and save battery voltage.

  if (millis()-oldTime > 5000) {
    oldTime = millis();
    SerialUSB.println("--------------------------");
    SerialUSB.println("BATTERY VOLTAGE MONITORING\n");
    SerialUSB.print("First cell  : ");
    SerialUSB.print(Robby.voltageCell1Read());
    SerialUSB.print(" V\nSecond cell : ");
    SerialUSB.print(Robby.voltageCell2Read());
    SerialUSB.print(" V\nThird cell  : ");
    SerialUSB.print(Robby.voltageCell3Read());
    SerialUSB.print(" V\n\nTotal voltage : ");
    SerialUSB.print(Robby.voltageBattRead());
    SerialUSB.println(" V\n");
  }
}