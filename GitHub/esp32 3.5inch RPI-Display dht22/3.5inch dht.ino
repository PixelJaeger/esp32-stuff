#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


#include "DHT.h"
#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

// Replace with your network credentials
const char* ssid     = "Nopedinger";
const char* password = "AlWu12031984sv.wrech";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

String temp_s;
String humi_s;


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
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
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


  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(150, 15, 150, 33, TFT_BLACK);
  tft.drawString(timeStamp,150,15,GFXFF);

  tft.fillRect(150, 90, 200, 33, TFT_BLACK);
  tft.drawString(dayStamp,150,90,GFXFF);

  temp_s = String(temp);
  tft.fillRect(220, 165, 150, 33, TFT_BLACK);
  tft.drawString(temp_s,220,165,GFXFF);
  
  humi_s = String(luft);
  tft.fillRect(290, 240, 100, 33, TFT_BLACK);
  tft.drawString(humi_s,290,240,GFXFF);
  
  delay(3000);

}
