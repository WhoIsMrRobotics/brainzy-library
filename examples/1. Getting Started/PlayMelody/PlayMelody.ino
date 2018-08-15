/*
 * PlayMelody
 * This example shows how to play a melody.
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
  delay(1000); // wait before to start
  melody();
}
 
void loop() {
  // put your setup code here, to run once:
  // DO NOTHING
}

void melody() {
  //Play first part
  firstPart();
 
  //Play second part
  secondPart();
 
  //Variant 1
  beep(NOTE_f, 4, 250);  
  beep(NOTE_gS,4, 500);  
  beep(NOTE_f, 4, 350);  
  beep(NOTE_a, 4, 125);
  beep(NOTE_c, 5, 500);
  beep(NOTE_a, 4, 375);  
  beep(NOTE_c, 5, 125);
  beep(NOTE_e, 5, 650);
 
  delay(500);
 
  //Repeat second part
  secondPart();
 
  //Variant 2
  beep(NOTE_f, 4, 250);  
  beep(NOTE_gS,4, 500);  
  beep(NOTE_f, 4, 375);  
  beep(NOTE_c, 5, 125);
  beep(NOTE_a, 4, 500);  
  beep(NOTE_f, 4, 375);  
  beep(NOTE_c, 5, 125);
  beep(NOTE_a, 4, 650);  
 
  delay(650);
}

void firstPart() {
  beep(NOTE_a, 4, 500);
  beep(NOTE_a, 4, 500);    
  beep(NOTE_a, 4, 500);
  beep(NOTE_f, 4, 350);
  beep(NOTE_c, 5, 150);  
  beep(NOTE_a, 4, 500);
  beep(NOTE_f, 4, 350);
  beep(NOTE_c, 5, 150);
  beep(NOTE_a, 4, 650);
 
  delay(500);
 
  beep(NOTE_e, 5, 500);
  beep(NOTE_e, 5, 500);
  beep(NOTE_e, 5, 500);  
  beep(NOTE_f, 5, 350);
  beep(NOTE_c, 5, 150);
  beep(NOTE_gS,4, 500);
  beep(NOTE_f, 4, 350);
  beep(NOTE_c, 5, 150);
  beep(NOTE_a, 4, 650);
 
  delay(500);
}
 
void secondPart() {
  beep(NOTE_a, 5, 500);
  beep(NOTE_a, 4, 300);
  beep(NOTE_a, 4, 150);
  beep(NOTE_a, 5, 500);
  beep(NOTE_gS,5, 325);
  beep(NOTE_g, 5, 175);
  beep(NOTE_fS,5, 125);
  beep(NOTE_f, 5, 125);    
  beep(NOTE_fS,5, 250);
 
  delay(325);
 
  beep(NOTE_aS,4, 250);
  beep(NOTE_dS,5, 500);
  beep(NOTE_d, 5, 325);  
  beep(NOTE_cS,5, 175);  
  beep(NOTE_c, 5, 125);  
  beep(NOTE_b, 4, 125);  
  beep(NOTE_c, 5, 250);  
 
  delay(350);
}

void beep(int note, int octave, unsigned long duration) {
  Robby.playNote(note, octave, duration); // play a note
  delay(duration+50);
}