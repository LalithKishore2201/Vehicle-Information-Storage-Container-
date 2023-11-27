#include "initial.h"
#include "lcd.h"
#include "gsm.h"
#include "ss.h"
#include "gps.h"


void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  dht.dht_read(DHTPIN);
  lcd.begin();
  lcd.backlight();

  attachInterrupt(digitalPinToInterrupt(CRASH_SENSOR), crash_ISR, HIGH);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(CRASH_SENSOR, INPUT);
  pinMode(ESP_PIN, OUTPUT);
  digitalWrite(ESP_PIN, LOW);
  if (digitalRead(8) == 0)
    gps();
  lcd.setCursor(3, 0);
  lcd.print("BLACK BOX");
  lcd.setCursor(5, 1);
  lcd.print("SYSTEM");
  delay(1000);

}

void loop() {

  if (digitalRead(CRASH_SENSOR) == 1) {
    Serial.println("ACCIDENT");
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("ACCIDENT");
    GSM_SEND();
    IOT("*ACCIDENT#");
    Serial.println("GSM SEND");
  }


  lcd.clear();
  dht.dht_read(DHTPIN);
  t = dht.temperature;
  Serial.println(t);
  lcd.setCursor(4, 0);
  lcd.print("T:");
  lcd.print(t);

  GAS_DATA = digitalRead(GAS_SENSOR);
  Serial.println(GAS_DATA);
  lcd.setCursor(10, 0);
  lcd.print("G:");
  lcd.print(GAS_DATA);


  if (GAS_DATA == 1) {
    lcd.setCursor(3, 1);
    lcd.print("Gas detected");
  }
  else {
    lcd.setCursor(1, 1);
    lcd.print("No Gas detected");
  }


SD_CARD_WRITE(String(GAS_DATA), String(t));
delay(1000);
IOT("@" + String(t) + "#" + "$" + String(GAS_DATA) + "#");

}

void crash_ISR() {
  CRASH_FLAG = true;
}

void IOT(String s) {
  for (int i = 0; i < s.length(); i++) {
    Serial.write(s[i]);
  }
  delay(3000);
}


void SD_CARD_WRITE(String s1, String s2) {

  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println();
    myFile.print("Gas: ");
    myFile.print(s1);
    myFile.print("\t");
    myFile.print("temp: ");
    myFile.print(s2);
    myFile.close();
    Serial.println("done.");
  }
  else {
    Serial.println("error opening test.txt");
  }
}
