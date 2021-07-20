//-----------------------------------------------------------------------------------
//  WIFI and thingspeak setup:

#include <WiFi.h>

const char* ssid = "HUJI-guest"; // your wifi SSID name
const char* password = "" ;// wifi pasword

WiFiClient client;

//-------------------------------------------------------------------------------------
// Set time
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 3600*3;  // For UTC +2.00 : 2 * 60 * 60 : 3600

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int time_h ; // variable for the hour
int time_m ; // variable for the hour

void setup() {
  Serial.begin(9600);
  //---------------------------------------------------------------------------
  //wifi conection:
    WiFi.disconnect();
    delay(10);
    WiFi.begin(ssid, password);
  
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  

   
    WiFi.begin(ssid, password);
    
   
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("NodeMcu connected to wifi...");
    Serial.println(ssid);
    Serial.println();
  //-----------------------------------------------------------------------
  // stings for time:
  timeClient.begin();

}

void loop() {
  timeClient.update();

  time_h = timeClient.getHours(); //You may need to correct it to Israel time
  time_m = timeClient.getMinutes(); //You may need to correct it to Israel time
  Serial.print("Time:");
  Serial.print(time_h); 
  Serial.print(":"); 
  Serial.print(time_m);    
  Serial.println();

  delay(1000);

}
