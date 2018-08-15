/*
 * CreateDestroyFile
 * This example shows how to create and destroy an SD card file.
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

File myFile;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200); // start USB communication (115200 bauds)

  SerialUSB.print("Initializing SD card...");

  if (!Robby.beginSD()) {
    SerialUSB.println("failed!");
    while(1);
  }
  SerialUSB.println("done.");

  if (SD.exists("example.txt")) {
    SerialUSB.println("example.txt exists.");
  } else {
    SerialUSB.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  SerialUSB.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    SerialUSB.println("example.txt exists.");
  } else {
    SerialUSB.println("example.txt doesn't exist.");
  }

  // delete the file:
  SerialUSB.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")) {
    SerialUSB.println("example.txt exists.");
  } else {
    SerialUSB.println("example.txt doesn't exist.");
  }
}

void loop() {
  // put your setup code here, to run once:
  // DO NOTHING
}