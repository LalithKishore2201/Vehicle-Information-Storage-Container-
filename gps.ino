#ifndef GPS_SEND_H
#define GPS_SEND_H
#include"ss.h"
//#include <LiquidCrystal.h>
//#include <SoftwareSerial.h>
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//SoftwareSerial serial(2,3);

void Send(String s);
void ggg();
void gps();
char str[70];
String gpsstr = "";
char *test = "$GPGGA";
long lat2, lon2;
String lat = "No Range      ";
String lon = "No Range     ";
int temp1 = 0, i, dis, j = 0;
boolean flag = 0;
char lat_a[] = "Norange123";
char lon_a[] = "Norange123";
long lat1 = 0, lon1 = 0;
float lat3 = 0.0 , lon3 = 0.0;


void GPS_SEND() {
  // put your main code here, to run repeatedly:
  //gps();
  Send("*" + String(lat3, 5) + "," + String(lon3, 5) + "#");
  delay(1000);
}


void ggg()
{
  gpsstr = "";
  while (1)
  {
    while (ss.available() > 0)
    {
      char inChar = (char)ss.read();
      gpsstr += inChar;
      i++;
      if (i < 7)
      {
        if (gpsstr[i - 1] != test[i - 1])
        {
          i = 0;
          gpsstr = "";
        }
      }
      if (inChar == '\r')
      {
        if (i > 65)
        {
          flag = 1;
          break;
        }
        else
        {
          i = 0;
        }
      }
    }
    if (flag)
      break;
  }
}

void gps()
{
  flag = 0;
  int x = 0;
  while (flag == 0)
  {
    ggg();
    flag = 1;
    int str_lenth = i;
    lat = "";
    lon = "";
    int comma = 0;
    while (x < str_lenth)
    {
      if (gpsstr[x] == '.')
      {
        x++;
        continue;
      }
      if (comma == 2)
        lat += gpsstr[x];
      else if (comma == 4)
        lon += gpsstr[x];
      if (gpsstr[x] == ',')
        comma++;

      x++;
    }
    int l1 = lat.length();
    lat[l1 - 1] = ' ';
    l1 = lon.length();
    lon[l1 - 1] = ' ';
    //lcd.clear();
    Serial.print("Lat:");
    Serial.println(lat);
    //lcd.setCursor(0, 0);
    //lcd.print(lat);
    Serial.print("Long:");
    Serial.println(lon);
    //lcd.setCursor(0, 1);
    //lcd.print(lon);


    while (j < 10)
    {
      lat_a[j] = lat[j];
      lon_a[j] = lon[j];
      j++;
    }

    lat1 = atol(lat_a);
    lon1 = atol(lon_a);

    lat2 = lat1 + 14539;
    lon2 = lon1 + 92416;

    lat3 = (float)lat2 / 1000000;
    lon3 = (float)lon2 / 1000000;

    Serial.print("Lat:");
    Serial.println(lat3, 6);
    //    lcd.setCursor(0, 0);
    //    lcd.print("LAT:");
    //    lcd.setCursor(0, 0);
    //    lcd.print(lat3, 6);
    Serial.print("Long:");
    Serial.println(lon3, 6);
    //    lcd.setCursor(0, 1);
    //    lcd.print("LONG:");
    //    lcd.setCursor(0, 1);
    //    lcd.print(lon3, 6);

    delay(2000);
    //    lcd.clear();
    i = 0; x = 0, j = 0;
    str_lenth = 0;
  }
}
//void Send(String s)
//{
//  for (i = 0; i < s.length(); i++)
//  {
//    Serial.write(s[i]);
//  }
//}
#endif
