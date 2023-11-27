#ifndef INITIAL_H
#define INITIAL_H

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include"dht11.h"
DHT dht;

File myFile;
#define CRASH_SENSOR 2
#define GAS_SENSOR 3
#define DHTPIN 4
#define ESP_PIN 5
int t;
int CRASH_DATA;
int GAS_DATA;
boolean CRASH_FLAG = false;
void CRASH_FUNCTION();
void IOT(String s);
void GSM_SEND();
void SD_CARD_WRITE(String s1, String s2) ;


#endif
