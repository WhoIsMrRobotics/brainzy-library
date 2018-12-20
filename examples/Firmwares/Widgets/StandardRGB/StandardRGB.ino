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
#define inputPin 9
#define led1pin 18
#define led2pin 19
#define led3pin 20

uint8_t colorRGB[3] = {0,0,0};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(12, inputPin, NEO_GRB+NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:

  byte address = 0x00;
  Serial.begin(115200);
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  
  delay(500);
  
  //Get raw values and remove noise using an exponential moving average
  int smoothValue = 0;
  for (int k=0; k < 500; k++) {
    float newValue = (float)analogRead(analogPin);
    float diff = abs(newValue - (float)smoothValue);
    float snap = 1. / (diff * 0.001 + 1.);
    snap = (1. - snap)*2.;
    if(snap > 1.) snap = 1.;
    smoothValue += (int)((newValue - (float)smoothValue) * snap);
    delay(1);
  }

  if (smoothValue < 124) {
    address = 0x01; //0
    digitalWrite(led1pin, HIGH);
  }
  else if (smoothValue > 124 && smoothValue < 343) {
    address = 0x02; //247.5
    digitalWrite(led2pin, HIGH);
  }
  else if (smoothValue > 343 && smoothValue < 482) {
    address = 0x03; //441.1
    digitalWrite(led1pin, HIGH);
    digitalWrite(led2pin, HIGH);
  }
  else if (smoothValue > 482 && smoothValue < 650) {
    address = 0x04; //524.4
    digitalWrite(led3pin, HIGH);
  }
  else if (smoothValue > 650 && smoothValue < 899) {
    address = 0x05; //775.5
    digitalWrite(led1pin, HIGH);
    digitalWrite(led3pin, HIGH);
  }
  else if (smoothValue > 899) {
    address = 0x06; //1023
    digitalWrite(led2pin, HIGH);
    digitalWrite(led3pin, HIGH);
  }
  
  Wire.begin(address);
  Wire.onReceive(receiveEvent);
  
  pixels.begin();
  pixels.show();
  
  pixels.setBrightness(50);
  pixels.setPixelColor(0, 0xff0000);
  pixels.setPixelColor(1, 0xff0000);
  pixels.setPixelColor(10, 0xff0000);
  pixels.setPixelColor(11, 0xff0000);
  pixels.setPixelColor(2, 0xffffff);
  pixels.setPixelColor(3, 0xffffff);
  pixels.setPixelColor(9, 0xffffff);
  pixels.setPixelColor(8, 0xffffff);
  pixels.setPixelColor(4, 0x0000ff);
  pixels.setPixelColor(5, 0x0000ff);
  pixels.setPixelColor(6, 0x0000ff);
  pixels.setPixelColor(7, 0x0000ff);
  pixels.show();

  delay(1000);
  for (uint8_t k = 0; k < pixels.numPixels(); k++) {
    pixels.setPixelColor(k, 0);
  }
  pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOTHING
}

void receiveEvent(int numBytes) {
  if (numBytes==4) {
    colorRGB[0] = Wire.read();
    colorRGB[1] = Wire.read();
    colorRGB[2] = Wire.read();

    uint32_t color = pixels.Color(colorRGB[0],colorRGB[1],colorRGB[2]);
    uint8_t id = Wire.read();

    if (id == 255) {
      for (uint8_t k = 0; k < pixels.numPixels(); k++) {
        pixels.setPixelColor(k, color);
      }
    }
    else pixels.setPixelColor(id, color);
  }
  else if (numBytes==1) {
    pixels.setBrightness(Wire.read());
  }
  pixels.show();
}