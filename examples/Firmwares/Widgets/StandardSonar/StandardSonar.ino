/*
 * StandardSonar
 * Standard firmware for Sonar Widget.
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

#include <Wire.h>

#define analogPin A6
#define trigPin 5 //8
#define echoPin 6 //9
#define led1pin 18
#define led2pin 19
#define led3pin 20

float distance = 0.;
bool disp = false;

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
  Wire.onRequest(requestEvent);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  unsigned long duration = pulseIn(echoPin, HIGH);
  distance = (float)duration/58.;
  distance = constrain(distance, 2., 400.);
  
  displayDistance();
  delay(100);
}

void requestEvent() {
  for (int i=0; i<4; i++) {
    Wire.write(*((unsigned char*)&distance + i));
  }
}

void displayDistance() {
  if (Serial.available()) {
    char rxByte = Serial.read();
    if (rxByte == 'd') disp = !disp;
  }
  if (disp) {
    Serial.print(distance);
    Serial.println(" cm");
  }
}

