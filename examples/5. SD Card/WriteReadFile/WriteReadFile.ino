/*
 * WriteReadFile
 * This example shows how to write and read text file in the SD card.
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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it.
  if (myFile) {
    SerialUSB.print("Writing to test.txt...");
    myFile.println("Hello, my name is Robby :D");
    myFile.close(); // close the file
    SerialUSB.println("done.");
  } else {
    // if the file didn't open, print an error.
    SerialUSB.println("failed!");
  }

  // re-open the file for reading.
  myFile = SD.open("test.txt");
  if (myFile) {
    SerialUSB.println("test.txt:");

    // read from the file until there's nothing else in it.
    while (myFile.available()) {
      SerialUSB.write(myFile.read());
    }
    myFile.close(); // close the file
  } else {
    // if the file didn't open, print an error.
    SerialUSB.println("error opening test.txt");
  }
}

void loop() {
  // put your setup code here, to run once:
  // DO NOTHING
}