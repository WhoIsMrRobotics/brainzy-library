#define STX    0x02
#define ETX    0x03
#define SLOW   750   // datafields refresh rate (ms)
#define FAST   250   // datafields refresh rate (ms)

long sendInterval = SLOW;                // interval between Buttons status transmission (milliseconds)

byte cmd[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // bytes received
long previousMillis = 0;                 // will store last time Buttons status was updated

void receivedSerialBluetoothData() {
  if(SerialBluetooth.available())  {
    delay(2);
    cmd[0] =  SerialBluetooth.read();  
    if(cmd[0] == STX)  {
      int i=1;      
      while(SerialBluetooth.available())  {
        delay(1);
        cmd[i] = SerialBluetooth.read();
        if(cmd[i]>127 || i>7)               break; // communication error
        if((cmd[i]==ETX) && (i==2 || i==7)) break; // button or Joystick data
        i++;
      }
      if     (i==2) getButtonState(cmd[1]); // 3 Bytes  (ex: < STX "C" ETX >)
      else if(i==7) getJoystickState(cmd);  // 6 Bytes  (ex: < STX "200" "180" ETX >)
    }
  } 
}

void sendSerialBluetoothData()  {
  static long previousMillis = 0;                             
  long currentMillis = millis();
  
  // send data back to smartphone
  if(currentMillis - previousMillis > sendInterval) {
    previousMillis = currentMillis; 
    /*
     * Data frame transmitted back from Arduino to Android device:
     * < 0X02   Buttons state   0X01   DataField#1   0x04   DataField#2   0x05   DataField#3    0x03 >
     * < 0X02      "01011"      0X01     "120.00"    0x04     "-4500"     0x05  "Motor enabled" 0x03 > (example)
     */
    SerialBluetooth.print((char)STX);                                             // start of Transmission
    SerialBluetooth.print(getButtonStatusString()); SerialBluetooth.print((char)0x1);   // buttons status feedback
    SerialBluetooth.print(Robby.xPositionRead());   SerialBluetooth.print((char)0x4);   // datafield #1
    SerialBluetooth.print(Robby.yPositionRead());   SerialBluetooth.print((char)0x5);   // datafield #2
    SerialBluetooth.print(Robby.angularPositionRead());                           // datafield #3
    SerialBluetooth.print((char)ETX);                                             // end of Transmission
  }  
}
