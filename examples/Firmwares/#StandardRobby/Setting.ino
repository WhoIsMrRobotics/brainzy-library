void eepromWrite(const char *text, int sz, int address) {
  for (int k=0; k < sz; k++) {
    EEPROM.update(address+k, *(text+k));
  }
}

void eepromRead(char *container, int sz, int address) {
  for (uint8_t k=0; k < sz; k++) {
    *(container+k) = EEPROM.read(address+k);
  }
}

/*
 * Define serial number
 */
bool writeSerialNumber() {
  String txt = "R";
  while(SerialUSB.available()>0) {
    txt += (char)getUSB();
  }
  if (txt.lastIndexOf("ROB-")==0) {
    SerialUSB.println("Define '"+txt+"' as new serial number...done.");
    eepromWrite(txt.c_str(), 11, EEPROM_SIZE-10);
  }
  return true;
}

/*
 * Define bluetooth name
 */
bool bluetoothNameWrite() {
  String txt;
  while(SerialUSB.available()>0) {
    txt += (char)getUSB();
  }
  SerialUSB.print("Define '"+txt+"' as new BT name...");
  String response = Robby.sendAT(SerialBluetooth,"AT+NAME="+txt,50);
  if (response.lastIndexOf("OK") > -1) USB.println("done.");
  else SerialUSB.println("failed.");
  return true;
}

/*
 * Define bluetooth password
 */
bool bluetoothPswdWrite() {
  String txt;
  while(USB.available()>0) {
    txt += (char)getUSB();
  }
  SerialUSB.print("Define '"+txt+"' as new BT password...");
  String response = Robby.sendAT(SerialBluetooth,"AT+PSWD="+txt,50);
  if (response.lastIndexOf("OK") > -1) SerialUSB.println("done.");
  else SerialUSB.println("failed.");
  return true;
}
