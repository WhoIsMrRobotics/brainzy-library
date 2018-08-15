/*
 * BlynkApp
 * Blynk is a platform to build iOS or Android apps to control Robby over the Internet.
 * You can easily build graphic interfaces for all your projects by simply dragging and dropping widgets.
 *
 * Download latest libraries here:
 *    https://github.com/WhoIsMrRobotics/brainzy-library/releases/latest
 *    https://github.com/blynkkk/blynk-library/releases/latest
 *
 * Visit Documentation pages here:
 *    https://www.mr-robotics.com/docs
 *    http://docs.blynk.cc/
 *
 * BRAINZY library is licensed under the GPL-3.0 license.
 * This example code is in the public domain.
 */

#include <BRAINZY.h>
#include <BRAINZY.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT SerialUSB

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

ESP8266 wifi(&SerialWifi);

void setup() {
  // Debug console
  SerialUSB.begin(115200);

  // Set ESP8266 baud rate
  SerialWifi.begin(115200);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop() {
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
