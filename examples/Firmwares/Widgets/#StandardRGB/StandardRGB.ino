/*
 * StandardRGB
 * Standard firmware for RGB Widget.
 *
 * Download latest libraries here:
 *    https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *    https://github.com/adafruit/Adafruit_NeoPixel/releases/latest
 *
 * Visit Documentation page here:
 *    https://www.mr-robotics.com/docs
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */

#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define analogPin A6
#define inputPin 5
#define led1pin 18
#define led2pin 19
#define led3pin 20
#define NUMPIXELS 8

uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, inputPin, NEO_GRB+NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:

  byte address = 0x00;
  Serial.begin(115200);
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  
  delay(500);
  
  int val = analogRead(analogPin);
  if (val < 124) {
    address = 0x01; //0
    digitalWrite(led1pin, HIGH);
  }
  else if (val > 124 && val < 343) {
    address = 0x02; //247.5
    digitalWrite(led2pin, HIGH);
  }
  else if (val > 343 && val < 482) {
    address = 0x03; //441.1
    digitalWrite(led1pin, HIGH);
    digitalWrite(led2pin, HIGH);
  }
  else if (val > 482 && val < 650) {
    address = 0x04; //524.4
    digitalWrite(led3pin, HIGH);
  }
  else if (val > 650 && val < 899) {
    address = 0x05; //775.5
    digitalWrite(led1pin, HIGH);
    digitalWrite(led3pin, HIGH);
  }
  else if (val > 899) {
    address = 0x06; //1023
    digitalWrite(led2pin, HIGH);
    digitalWrite(led3pin, HIGH);
  }
  
  Wire.begin(address);
  Wire.onReceive(receiveEvent);
  pixels.begin();
  
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(R,G,B));
  }
  pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}

void receiveEvent(int numBytes) {
  if (numBytes==3) {
    R = Wire.read();
    G = Wire.read();
    B = Wire.read();

    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(R,G,B));
    }
    pixels.show();
  }
}