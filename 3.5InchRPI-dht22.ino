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

const char* ssid     = "SSID HIER";
const char* password = "PASSWORT HIER";

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


// Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(7200);

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

  tft.setFreeFont(FSB18);       // Select Free Serif 12 point font
  tft.println();                // Move cursor down a line
  tft.print("Datum: ");
  tft.print(dayStamp); // Print the font name onto the TFT screen

  tft.setFreeFont(FSB18);       // Select Free Serif 12 point font
  tft.println();                // Move cursor down a line
  tft.print("Temperatur: ");
  tft.print(temp);
  
  tft.setFreeFont(FSB18);       // Select Free Serif 24 point font
  tft.println();                // Move cursor down a line
  tft.print("Luftfeuchtigkeit: ");
  tft.print(luft); // Print the font name onto the TFT screen
  

  delay(30000);

}

// Print the header for a display screen
void header(const char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.fillRect(0, 0, 480, 30, TFT_BLACK);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(string, 239, 2, 4); // Font 4 for fast drawing with background
}

// Draw a + mark centred on x,y
void drawDatum(int x, int y)
{
  tft.drawLine(x - 5, y, x + 5, y, TFT_GREEN);
  tft.drawLine(x, y - 5, x, y + 5, TFT_GREEN);
}
