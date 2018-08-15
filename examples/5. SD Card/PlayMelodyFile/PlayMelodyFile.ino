/*
 * PlayMelodyFile
 * This example shows how to play a melody stored in the SD card.
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

char melody[] = "#500a4,500a4,500a4,350f4,150c5,500a4,350f4,150c5,650a4,500-,500e5,500e5,500e5,350f5,150c5,500gS4,350f4,150c5,650a4";

File myFile;

void setup() {
  // put your setup code here, to run once:
  Robby.beginSD();
  if (SD.exists("starwars.txt")) {
    SD.remove("starwars.txt");
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("starwars.txt", FILE_WRITE);
  myFile.print(melody);
  myFile.close(); // close the file

  // re-open the file for reading and playing music.
  Robby.playFile("starwars.txt");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Do not use the delay () or other functions with which your program is paused !
  Robby.playMelodyProcess(); // run all pre-program function for playing melody
}