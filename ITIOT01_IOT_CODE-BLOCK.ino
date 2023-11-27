#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<SoftwareSerial.h>
SoftwareSerial ss(D1, D2);//rx tx
/************************* WiFi Access Point *********************************/
String tdata, hdata, bpdata, f1data, f2data, f3data;
int count = 0, count1 = 0, count2 = 0, count3 = 0,  count4 = 0, count5 = 0, uvc = 0;
#define WLAN_SSID       "mk"
#define WLAN_PASS       "12345678"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "e1589e"
#define AIO_KEY         "aio_Pdqb98KEyvuMUCO0PYbpg59rnbzd"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish FEED = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/info");
Adafruit_MQTT_Publish TEMP = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish HUMIDITY = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gas");
Adafruit_MQTT_Publish PHVALUE = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");
Adafruit_MQTT_Publish GAS = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");
Adafruit_MQTT_Publish SOIL = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/");


Adafruit_MQTT_Subscribe control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/control");


//Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
char tdata1[50];
char hdata1[5];
char bpdata1[10];
char f1data1[5];
char f2data1[5];
char f3data1[5];
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  delay(10);

  Serial.println(F("Adafruit MQTT"));
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&control);
}

void loop() {

  MQTT_connect();
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;
  count5 = 0;
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  f2data = "";
  f3data = "";
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    // Serial.print(c);
    if (c == '*')
    {
      while (Serial.available() > 0)
      {
        char t = Serial.read();
        if (count == 50)
        {
          break;
        }
        if (t == '#') {
          break;
        }
        tdata += t;
        count++;
      }
    }
    if (c == '@')
    {
      while (Serial.available() > 0)
      {
        char h = Serial.read();
        if (count1 == 2)
        {
          break;
        }
        if (h == '#') {
          break;
        }
        hdata += h;
        count1++;
      }
    }
    if (c == '$')
    {
      while (Serial.available() > 0)
      {
        char u = Serial.read();
        if (count2 == 1)
        {
          break;
        }
        if (u == '#') {
          break;
        }
        bpdata += u;
        count2++;
      }
    }
    if (c == '^')
    {
      while (Serial.available() > 0)
      {
        char v = Serial.read();
        if (count3 == 1)
        {
          break;
        }
        if (v == '#') {
          break;
        }
        f1data += v;
        count3++;
      }
    }
    if (c == '&')
    {
      while (Serial.available() > 0)
      {
        char l = Serial.read();
        if (count4 == 1)
        {
          break;
        }
        if (l == '#') {
          break;
        }
        f2data += l;
        count4++;
      }
    }
    if (c == '!')
    {
      while (Serial.available() > 0)
      {
        char l = Serial.read();
        if (count5 == 1)
        {
          break;
        }
        if (l == '#') {
          break;
        }
        f3data += l;
        count5++;
      }
    }
  }

  if ( tdata.length() > 0 )
  {
    for (int i = 0; i < 50; i++) {
      tdata1[i] = tdata[i];
    }

    Serial.println(tdata1);
    FEED.publish(tdata1);
    tdata = "";

    delay(2000);
  }

  if ( hdata.length() > 0 )
  {
    for (int i = 0; i < 2; i++) {
      hdata1[i] = hdata[i];
    }
    Serial.println(hdata1);
    TEMP.publish(hdata1);
    hdata = "";
    delay(2000);
  }
  if ( bpdata.length () > 0 )
  {
    for (int i = 0; i < 2; i++) {
      bpdata1[i] = bpdata[i];
    }

    Serial.println(bpdata1);
    HUMIDITY.publish(bpdata1);
    bpdata = "";
    delay(2000);
  }
  if ( f1data.length () > 0 )
  {
    for (int i = 0; i < 1; i++) {
      f1data1[i] = f1data[i];
    }

    Serial.println(f1data1);
    PHVALUE.publish(f1data1);
    f1data = "";
    delay(2000);
  }
  if ( f2data.length () > 0 )
  {
    for (int i = 0; i < 1; i++) {
      f2data1[i] = f2data[i];
    }
    Serial.println(f2data );
    GAS.publish(f2data1);
    f2data = "";
    delay(2000);
  }
  if ( f3data.length () > 0 )
  {
    for (int i = 0; i < 1; i++) {
      f3data1[i] = f3data[i];
    }
    Serial.println(f3data );
    SOIL.publish(f3data1);
    f3data = "";
    delay(2000);
  }
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  f2data = "";
  f3data = "";
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;
  count5 = 0;
  delay(100); // ThingSpeak will only accept updates every 15 seconds.


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &control) {
      Serial.print(F("Got: "));
      Serial.println((char *)control.lastread);
    }
    if (strcmp((char *)control.lastread, "1") == 0) {
      digitalWrite(D4, LOW);
      FEED.publish("AUTO MODE");

    }

    if (strcmp((char *)control.lastread, "2") == 0) {
      digitalWrite(D4, HIGH);
      FEED.publish("MANUAL MODE");

    }
    if (strcmp((char *)control.lastread, "3") == 0) {
      Serial.write('2');
      FEED.publish("MOTOR ON");

    }
    if (strcmp((char *)control.lastread, "4") == 0) {
      Serial.write('3');
      FEED.publish("MOTOR OFF");

    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
