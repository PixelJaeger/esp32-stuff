#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#include "DHT.h"
#define ARRAYSIZE 10
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

unsigned long drawTime = 0;

// Replace with your network credentials
const char* ssid     = "iReallyHateC";
const char* password = "gimmePythonOrgimmeDeath!";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

String temp_s;
String humi_s;

String cuttime;

String oldday;
String oldtemp;
String oldhumi;
String oldtime;

String bottomtext[ARRAYSIZE] = {
  "A Python() a day keeps the C-Compiler away!",
  "If you can read this you're way to close!",
  "It hurts when IP ain't funny! Go see a DNS!",
  " {(.) O.O (.)} Tiddie McEarmuffs, Best Device ever!",
  "I ran out of puns. Have a nice \"sod off!\" instead!",
  "42 isn't the answer to everything. Ask Chuck Norris instead!",
  "I'm here to chew gum and kick ass! But what is this C shit?!",
  "Duke Nukem Forever is a good game! Do i get paid now?",
  "Crouching C Code, hidden PythonBomb",
  "Wanna C(my)PP sounds bad. Wanna see my python sound better!"
};

int rnd_q;
int old_q;

// mogel and schleife can be adjusted to your preference
// Due to limitations of the DHT22 do not set schleife below 2000
int mogel = 0;
int schleife = 10000;


void setup(void) {

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);


  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextPadding(60);
  tft.setFreeFont(FSB18);

  tft.drawString("Uhrzeit:",15,15,GFXFF);
  tft.drawString("Datum:",15,90, GFXFF);
  tft.drawString("Temperatur:",15,165,GFXFF);

  //disgusting hack since the font can't display a "°"
  tft.setFreeFont(FSB9);
  tft.drawString("o",305,165,GFXFF);
  tft.setFreeFont(FSB18);
  tft.drawString("C",315,165,GFXFF);

  tft.drawString("Luftfeuchtigkeit:",15,240,GFXFF);
  tft.drawString("%",370,240,GFXFF);

}

void loop() {
  // to-do: alle 2(?) stunden wifi an und neues ntp holen
  
  float luft = dht.readHumidity();
  float temp = dht.readTemperature();


  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();

  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  cuttime = timeStamp.substring(0,5);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setFreeFont(FSB18);

  if (cuttime != oldtime) {
  tft.fillRect(150, 15, 150, 33, TFT_BLACK);
  delay(mogel);
  tft.drawString(cuttime,150,15,GFXFF);
  oldtime == cuttime;
  }

  if (dayStamp != oldday) {
  tft.fillRect(150, 90, 200, 33, TFT_BLACK);
  delay(mogel);
  tft.drawString(dayStamp,150,90,GFXFF);
  oldday = dayStamp;
  }

  temp_s = String(temp);
  if (temp_s != oldtemp) {
  tft.fillRect(220, 165, 50, 33, TFT_BLACK);
  delay(mogel);
  tft.drawString(temp_s,220,165,GFXFF);
  oldtemp = temp_s;
  }

  humi_s = String(luft);
  if (humi_s != oldhumi) {
  tft.fillRect(290, 240, 50, 33, TFT_BLACK);
  delay(mogel);
  tft.drawString(humi_s,290,240,GFXFF);
  oldhumi = humi_s;
  }

  rnd_q = random(0,9);
  if (rnd_q != old_q) {
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  tft.setFreeFont(FSB9);
  tft.fillRect(5, 300, 475, 20, TFT_BLACK);
  tft.drawString(bottomtext[rnd_q],5,300,GFXFF);
  old_q = rnd_q;
  }

  delay(schleife);

}
