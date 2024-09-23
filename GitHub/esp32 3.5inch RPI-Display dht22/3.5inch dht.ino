#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h"

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "DHT.h"
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

TFT_eSPI tft = TFT_eSPI();

const char* ssid     = "ItHurtsWhenIP";
const char* password = "StHe22031996mac.sux";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

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

unsigned long drawTime = 0;

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
  // GMT +1 = 3600
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextPadding(120);
  tft.setFreeFont(FSB18);

  tft.drawString("Uhrzeit:",15,15,GFXFF);
  tft.drawString("Datum:",15,90, GFXFF);
  tft.drawString("Temperatur:",15,165,GFXFF);
  tft.drawString("Luftfeuchtigkeit:",15,240,GFXFF);

}

void loop() {

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

  if (cuttime != oldtime) {
  tft.fillRect(150, 15, 150, 33, TFT_BLACK);
  tft.drawString(cuttime,150,15,GFXFF);
  oldtime == cuttime;
  }

  if (dayStamp != oldday) {
  tft.fillRect(150, 90, 200, 33, TFT_BLACK);
  tft.drawString(dayStamp,150,90,GFXFF);
  oldday = dayStamp;
  }

  temp_s = String(temp);
  if (temp_s != oldtemp) {
  tft.fillRect(220, 165, 150, 33, TFT_BLACK);
  tft.drawString(temp_s,220,165,GFXFF);
  oldtemp = temp_s;
  }

  humi_s = String(luft);
  if (humi_s != oldhumi) {
  tft.fillRect(290, 240, 100, 33, TFT_BLACK);
  tft.drawString(humi_s,290,240,GFXFF);
  oldhumi = humi_s;
  }

  delay(5000);

}


// todo: different ntp, reask ntp for time every 2ish hours
