/*
 * Check button
 */
bool checkButton() {
  static bool first = true;
  if (first) {
    SerialUSB.print("Button is testing...Please, press the button...");
    first = false;
  }
  else if (Robby.isButtonReleased()) {
    SerialUSB.println("Done.");
    first = true;
  }
  return first;
}

/*
 * Check Bluetooth
 */
bool checkBuetooth() {
  SerialUSB.print("Bluetooth is testing...");
  String response = Robby.sendAT(SerialBluetooth,"AT",50);
  if (response.lastIndexOf("OK") > -1) {
    SerialUSB.println("done.");
  }
  else SerialUSB.println("failed.");
  return true;
}

/*
 * Check Wifi
 */
bool checkWifi() {
  SerialUSB.print("Wifi is testing...");
  String response = Robby.sendAT(SerialWifi,"AT",50);
  if (response.lastIndexOf("OK") > -1) {
    SerialUSB.println("done.");
  }
  else SerialUSB.println("failed.");
  return true;
}

/*
 * Check battery
 */
bool checkBattery() {
  float c1 = Robby.voltageCell1Read();
  float c2 = Robby.voltageCell2Read();
  float c3 = Robby.voltageCell3Read();

  if (c1<1. && c2<1. && c3<1.) {
    SerialUSB.println("Please, connect the balance connector to monitor your battery.");
  }
  else {
    SerialUSB.print("Battery cell 1 is testing...");
    if (c1>2.5) SerialUSB.println("done.");
    else USB.println("failed.");
    SerialUSB.print("Battery cell 2 is testing...");
    if (c2>2.5) SerialUSB.println("done.");
    else USB.println("failed.");
    SerialUSB.print("Battery cell 3 is testing...");
    if (c3>2.5) SerialUSB.println("done.");
    else USB.println("failed.");
  }
  return true;
}

/*
 * Check motor
 */
bool checkMotor(int motorid) {
  static bool first = true;
  static unsigned long oldtime = 0;

  Robby.resetWheelAngularPositions();
  
  if (first) {
    if (motorid == LEFTMOTOR) {
      Robby.leftMotorWrite(255);
      SerialUSB.print("Left motor is testing...");
    }
    else if (motorid == RIGHTMOTOR) {
      Robby.rightMotorWrite(255);
      SerialUSB.print("Right motor is testing...");
    }
    else if (motorid == FRONTMOTOR) {
      Robby.frontMotorWrite(255);
      SerialUSB.print("Front motor is testing...");
    }
    else {
      SerialUSB.println("This motor ID doesn't exist.");
      return first;
    }
    oldtime = millis();
    first = false;
  }
  else if (Robby.leftMotorPositionRead()>360 || Robby.rightMotorPositionRead()>360 || Robby.frontMotorPositionRead()>360) {
    Robby.stop();
    SerialUSB.println("Done.");
    first = true;
  }
  else if (millis()-oldtime>2000) {
    Robby.stop();
    SerialUSB.println("failed.");
    first = true;
  }
  return first;
}


/*
 * Check all hardware components
 */
bool checkhardware() {
  static int s = 1;
  bool result = false;
  if (s==1 && checkButton()) s++;
  else if (s==2 && checkBuetooth()) s++;
  else if (s==3 && checkWifi()) s++;
  else if (s==4 && checkBattery()) s++;
  else if (s==5 && checkMotor(LEFTMOTOR)) s++;
  else if (s==6 && checkMotor(RIGHTMOTOR)) s++;
  else if (s==7 && checkMotor(FRONTMOTOR)) s++;
  else if (s==8) {
    tone(BUILTIN_BUZZER, 1500, 100);
    SerialUSB.println("Please check by yourself the following components : Buzzer / Led / Led button");
    s = 1;
    result = true;
  }
  return result;
}