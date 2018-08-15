/*
 * PlayMelodyWithoutDelay
 * This example shows how to play a melody without blocking functions.
 *
 * Download latest BRAINZY library here:
 *		https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *
 * Visit Documentation page here:
 *		https://www.mr-robotics.com/docs
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */

#include <BRAINZY.h> // include the robot library

char melody[] = "#500a4,500a4,500a4,350f4,150c5,500a4,350f4,150c5,650a4,500-,500e5,500e5,500e5,350f5,150c5,500gS4,350f4,150c5,650a4";

void setup() {
  // put your setup code here, to run once:
  delay(1000);               // wait before to start
  Robby.ledBlink(100);       // blink led on board in the same time
  Robby.playMelody(melody);  // play the melody
}

void loop() {
  // put your main code here, to run repeatedly:
  // Do not use the delay () or other functions with which your program is paused !
  Robby.playMelodyProcess(); // run all pre-program function for playing melody
}