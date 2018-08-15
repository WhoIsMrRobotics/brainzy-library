#include <BRAINZY.h>            //https://github.com/oleveque/BRAINZY
#include <ESP8266WiFi.h>        //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>        //https://github.com/tzapu/WiFiManager

String txt;
char serialnumber[11];
char state = '0';

void setup() {
  WiFiManager wifiManager;
  //wifiManager.resetSettings(); //reset saved settings
  wifiManager.autoConnect("AutoConnectRobby");
  
  Robby.setMode(OMNIDIRECTIONAL);
  Robby.alarmBattOff();
  Robby.noSlaved();
  
  SerialUSB.begin(115200);
  SerialUSB.setTimeout(10);
  SerialBluetooth.begin(38400);
  SerialWifi.begin(115200);

  Robby.ledOn();
  Robby.ledBlink(500);
  Robby.ledButtonBlink(500);

  Robby.getSerialNumber(serialnumber);
}

void loop() {
  if (SerialUSB.available()>0) state = (char)getUSB();
  
  switch (state) {
    case '0' : 
      if (mainMenu()) state = '#';
      break;
    case '1' : 
      if (checkhardware()) state = '#';
      break;
    case 'a' : 
      if (checkButton()) state = '#';
      break;
    case 'b' : 
      if (checkBuetooth()) state = '#';
      break;
    case 'c' :
      if (checkWifi()) state = '#';
      break;
    case 'd' :
      if (checkBattery()) state = '#';
      break;
    case 'e' : 
      if (checkMotor(LEFTMOTOR)) state = '#';
      break;
    case 'f' : 
      if (checkMotor(RIGHTMOTOR)) state = '#';
      break;
    case 'g' : 
      if (checkMotor(FRONTMOTOR)) state = '#';
      break;
    case '2' :
      if (bluetoothNameWrite()) state = '#';
      break;
    case '3' :
      if (bluetoothPswdWrite()) state = '#';
      break;
    case '4' :
      Robby.sendAT(SerialBluetooth,"AT+VERSION?",50,true);
      state = '#';
      break;
    case '5' :
      txt = "";
      while(SerialUSB.available()>0) {
        txt += (char)getUSB();
      }
      Robby.sendAT(SerialBluetooth,txt,1000,true);
      state = '#';
      break;
    case '6' :
      Robby.sendAT(SerialWifi,"AT+GMR",50,true);
      state = '#';
      break;
    case '7' :
      txt = "";
      while(SerialUSB.available()>0) {
        txt += (char)getUSB();
      }
      Robby.sendAT(SerialWifi,txt,1000,true);
      state = '#';
      break;
    case 'R' :
      if (writeSerialNumber()) state = '#';
      break;
  }
}

bool mainMenu() {
  SerialUSB.println("---");
  SerialUSB.print("BRAINZY Board v3.2 -- ");
  SerialUSB.println(serialnumber);
  SerialUSB.println("(c) 2018, Mr. Robotics");
  SerialUSB.println();
  SerialUSB.println("\t 0. Main menu.");
  SerialUSB.println("> HARDWARE");
  SerialUSB.println("\t 1. Check all hardware.");
  SerialUSB.println("\t\t a. Check button.");
  SerialUSB.println("\t\t b. Check bluetooth.");
  SerialUSB.println("\t\t c. Check wifi.");
  SerialUSB.println("\t\t d. Check battery.");
  SerialUSB.println("\t\t e. Check left motor.");
  SerialUSB.println("\t\t f. Check right motor.");
  SerialUSB.println("\t\t g. Check front motor.");
  SerialUSB.println("> BLUETOOTH SETTING");
  SerialUSB.println("\t 2. Define bluetooth name.");
  SerialUSB.println("\t 3. Define bluetooth password.");
  SerialUSB.println("\t 4. Get Bluetooth firmware version.");
  SerialUSB.println("\t 5. Send AT command to Bluetooth module.");
  SerialUSB.println("> WIFI SETTING");
  SerialUSB.println("\t 6. Get Wifi firmware version.");
  SerialUSB.println("\t 7. Send AT command to Wifi module.");
  SerialUSB.println("---");
  SerialUSB.println();
  return true;
}

int getUSB() {
  static int lastrx = 35;
  int rx = SerialUSB.read();
  if (rx==13 || rx==10) rx = lastrx;
  else lastrx = rx;
  return rx;
}

bool getStringUSB(String* container) {
  if (SerialUSB.available()>0) {
    *container = SerialUSB.readString();
    return true;
  }
  else return false;
}
