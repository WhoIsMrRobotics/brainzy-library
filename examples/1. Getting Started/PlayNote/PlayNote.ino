/*
 * PlayNote
 * This example shows how to play a note.
 * You can play 12 differents notes on 4 differents octaves:
 *    Do using NOTE_c,
 *    Do# using NOTE_cS,
 *    Ré using NOTE_d,
 *    Ré# using NOTE_dS,
 *    Mi using NOTE_e,
 *    Fa using NOTE_f,
 *    Fa# using NOTE_fS,
 *    Sol using NOTE_g,
 *    Sol# using NOTE_gS,
 *    La using NOTE_a,
 *    La# using NOTE_aS,
 *    Si using NOTE_b
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

void setup() {
  // put your setup code here, to run once:
  for (int octave = 4; octave <8; octave++) {
    delay(1000);
    Robby.playNote(NOTE_c, octave); //Do
    delay(1000);
    Robby.playNote(NOTE_d, octave); //Ré
    delay(1000);
    Robby.playNote(NOTE_e, octave); //Mi
    delay(1000);
    Robby.playNote(NOTE_f, octave); //Fa
    delay(1000);
    Robby.playNote(NOTE_g, octave); //Sol
    delay(1000);
    Robby.playNote(NOTE_a, octave); //La
    delay(1000);
    Robby.playNote(NOTE_b, octave); //Si
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}