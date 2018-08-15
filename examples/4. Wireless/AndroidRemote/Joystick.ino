void getJoystickState(byte data[8])    {
  int joyX = (data[1]-48)*100 + (data[2]-48)*10 + (data[3]-48); // obtain the int from the ASCII representation
  int joyY = (data[4]-48)*100 + (data[5]-48)*10 + (data[6]-48);
  joyX = joyX - 200;                                            // offset to avoid
  joyY = joyY - 200;                                            // transmitting negative numbers

  if(joyX<-100 || joyX>100 || joyY<-100 || joyY>100) return;    // commmunication error
  
  /* Your code here...*/
  Robby.speedWrite(map(joyY,-100,100,-255,255), map(joyX,-100,100,255,-255)); // example
}
