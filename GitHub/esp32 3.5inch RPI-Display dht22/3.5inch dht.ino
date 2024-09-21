
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

const char* ssid     = "SSDI HIER";
const char* password = "Passwort Hier";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String dayStamp;
String timeStamp;

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
  timeClient.setTimeOffset(3600);

}

void loop() {

  float luft = dht.readHumidity();
  float temp = dht.readTemperature();

  int xpos =  0;
  int ypos = 40;

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();

  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

  tft.fillScreen(TFT_BLACK);

  header("My urge to kill is rising!");


  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(xpos, ypos);

  tft.setFreeFont(FSB18);
  tft.println();
  tft.print("Uhrzeit: ");
  tft.print(timeStamp);

  tft.setFreeFont(FSB18);
  tft.println();
  tft.print("Datum: ");
  tft.print(dayStamp);

  tft.setFreeFont(FSB18);
  tft.println();
  tft.print("Temperatur: ");
  tft.print(temp);
  
  tft.setFreeFont(FSB18);
  tft.println();
  tft.print("Luftfeuchtigkeit: ");
  tft.print(luft);
  
  delay(30000);
}


void header(const char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.fillRect(0, 0, 480, 30, TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(string, 239, 2, 4);
}


#ifndef LOAD_GLCD
//ERROR_Please_enable_LOAD_GLCD_in_User_Setup
#endif

#ifndef LOAD_FONT2
//ERROR_Please_enable_LOAD_FONT2_in_User_Setup!
#endif

#ifndef LOAD_FONT4
//ERROR_Please_enable_LOAD_FONT4_in_User_Setup!
#endif

#ifndef LOAD_FONT6
//ERROR_Please_enable_LOAD_FONT6_in_User_Setup!
#endif

#ifndef LOAD_FONT7
//ERROR_Please_enable_LOAD_FONT7_in_User_Setup!
#endif

#ifndef LOAD_FONT8
//ERROR_Please_enable_LOAD_FONT8_in_User_Setup!
#endif

#ifndef LOAD_GFXFF
ERROR_Please_enable_LOAD_GFXFF_in_User_Setup!
#endif

