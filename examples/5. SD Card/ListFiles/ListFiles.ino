/*
 * ListFiles
 * This example shows how print out the files in a directory on a SD card.
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

File root;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200); // start USB communication (115200 bauds)

  SerialUSB.print("Initializing SD card...");

  if (!Robby.beginSD()) {
    SerialUSB.println("failed!");
    while(1);
  }
  SerialUSB.println("done.");

  root = SD.open("/");

  printDirectory(root, 0);

  SerialUSB.println("done!");
}

void loop() {
  // put your setup code here, to run once:
  // DO NOTHING
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      SerialUSB.print('\t');
    }
    SerialUSB.print(entry.name());
    if (entry.isDirectory()) {
      SerialUSB.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      SerialUSB.print(" .. ");
      SerialUSB.print(entry.size(), DEC);
      SerialUSB.println(" bytes");
    }
    entry.close();
  }
}