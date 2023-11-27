#ifndef GSM_H
#define GSM_H
#include"ss.h"

#include "gps.h"
//float lat3 =13.03652 , lon3 = 80.23077;
void GSM_SEND() {
  // put your main code here, to run repeatedly:

  ss.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  ss.println("AT+CMGS=\"+917358500863\"\r"); // Replace x with mobile number
  delay(1000);
  ss.println("ACCIDENT....");// The SMS text you want to send
  delay(100);
  ss.println("https://www.google.com/maps/?q=");
  //ss.print(lat3);
  ss.print("14.02");
  ss.print(",");
  ss.print("16.03");
  //ss.print(lon3);
  ss.println((char)26);// ASCII code of CTRL+Z
  delay(3000);

}
#endif
