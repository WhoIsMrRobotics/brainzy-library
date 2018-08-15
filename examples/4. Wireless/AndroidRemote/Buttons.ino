byte buttonStatus = 0;                   // first Byte sent to Android device
String displayStatus = "xxxx";           // message to Android device

String getButtonStatusString()  {
  String bStatus = "";
  for(int i=0; i<6; i++)  {
    if(buttonStatus & (B100000 >>i)) bStatus += "1";
    else bStatus += "0";
  }
  return bStatus;
}

void getButtonState(int bStatus)  {
  switch (bStatus) {
    /*
     * --- Button 1 ---
     */
    case 'A':
      buttonStatus |= B000001; // ON
      SerialUSB.println("\n** Button 1: ON **");
      
      /* Your code here...*/     
      displayStatus = "LED <ON>"; // demo text message
      SerialUSB.println(displayStatus);
      Robby.ledButtonOn();
      /* End...*/  
      
      break;
    case 'B':
      buttonStatus &= B111110; // OFF
      SerialUSB.println("\n** Button 1: OFF **");
      
      /* Your code here...*/
      displayStatus = "LED <OFF>"; // demo text message
      SerialUSB.println(displayStatus);
      Robby.ledButtonOff();
      /* End...*/  
      
      break;

    /*
     * --- Button 2 ----
     */
    case 'C':
      buttonStatus |= B000010; // ON
      SerialUSB.println("\n** Button 2: ON **");
      
      /* Your code here...*/
      displayStatus = "Button 2 <ON>";
      SerialUSB.println(displayStatus);
      /* End...*/
      
      break;
    case 'D':
      buttonStatus &= B111101; // OFF
      SerialUSB.println("\n** Button 2: OFF **");
      
      /* Your code here...*/
      displayStatus = "Button 2 <OFF>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;

    /*
     * --- Button 3 ---
     */
    case 'E':
      buttonStatus |= B000100; // ON
      SerialUSB.println("\n** Button 3: ON **");
      
      /* Your code here...*/
      displayStatus = "Button 3 <ON>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;
    case 'F':
      buttonStatus &= B111011; // OFF
      SerialUSB.println("\n** Button 3: OFF **");
      
      /* Your code here...*/
      displayStatus = "Button 3 <OFF>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;

    /*
     * --- Button 4 ---
     */
    case 'G':
      buttonStatus |= B001000; // ON
      SerialUSB.println("\n** Button 4: ON **");
      
      /* Your code here...*/
      displayStatus = "Button 4 <ON>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;
    case 'H':
      buttonStatus &= B110111; // OFF
      SerialUSB.println("\n** Button 4: OFF **");
      
      /* Your code here...*/
      displayStatus = "Button 4 <OFF>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;

    /*
     * --- Button 5 --- (configured as momentary button)
     */
    case 'I':
      //buttonStatus |= B010000; // ON
      SerialUSB.println("\n** Button 5: ++ pushed ++ **");
      
      /* Your code here...*/
      displayStatus = "Button 5: <pushed>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;
//    case 'J':
//      buttonStatus &= B101111; // OFF
//      /* Your code here...*/
//      SerialUSB.println(displayStatus);
//      /* End...*/ 
//      break;


    /*
     * --- Button 6 ---
     */
    case 'K':
      buttonStatus |= B100000; // ON
      SerialUSB.println("\n** Button 6: ON **");
      
      /* Your code here...*/
      displayStatus = "Button 6 <ON>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;
    case 'L':
      buttonStatus &= B011111; // OFF
      SerialUSB.println("\n** Button 6: OFF **");
      
      /* Your code here...*/
      displayStatus = "Button 6 <OFF>";
      SerialUSB.println(displayStatus);
      /* End...*/ 
      
      break;
  }
}
