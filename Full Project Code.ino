#include <HX711.h>
#include "i2cArduino.h"
#include <WiFi.h>
#include "ThingSpeak.h"
#include <NTPClient.h>
#include <WiFiUdp.h>


//// defenitios:
// time
const long utcOffsetInSeconds = 3600*3;  // For UTC +2.00 : 2 * 60 * 60 : 3600

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int time_h ; // variable for the hour
int time_m ; // variable for the hour

/// sensor

SVCS3 vcs;
float vwc;

float HT=30;
///valve
const int relay1 = 26;
const int relay2 = 25;
const int relay3 = 32;
int relay1_state;
int relay2_state;
int relay3_state;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 17;
const int LOADCELL_SCK_PIN = 18;
float zero;
float weight;
HX711 scale;


// Thingspeaksetup
unsigned long myChannelNumber = 1374548;
const char * myWriteAPIKey = "BXHUOASQ8HTBX4B1";

const char* ssid = "HUJI-guest"; // your wifi SSID name
const char* password = "" ;// wifi pasword
 
const char* server = "api.thingspeak.com";

WiFiClient client;


void setup() {
  ///valve
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
 
  
/////sensor

  vcs.init(0x63);
  
//// weight

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
   if (scale.is_ready()) {
    long reading = scale.read();
    //Serial.print("HX711 reading: ");
    zero = reading*0.0189-50;
  } else {
    Serial.println("HX711 not found.");
  } 
// thingspeak

  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

    ThingSpeak.begin(client);
 
  WiFi.begin(ssid, password);
  
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();

    // stings for time:
  timeClient.begin(); 
  delay(5000);
} 


void loop() {
  for (int i = 0; i<=15; i++);{
///valve 1: time
      timeClient.update();
      time_h = timeClient.getHours(); //You may need to correct it to Israel time
      time_m = timeClient.getMinutes(); //You may need to correct it to Israel time
      if (time_h ==13 and time_m<2) {
        digitalWrite(relay1, LOW);
        relay1_state = 1;
        }
        else {
          digitalWrite(relay1, HIGH);
        relay1_state = 0;
        }
      Serial.print("Time:");
      Serial.print(time_h); 
      Serial.print(":"); 
      Serial.print(time_m);    
      Serial.println();
    
///valve 2: sensor
      
      vcs.newReading(); // start sensor reading
      delay(100); //let sensor read data
    
    //getting values one by one
      float e25 = vcs.getE25();
      float ec = vcs.getEC();
      float temp = vcs.getTemp();
    ///vwc - moisture 
      float vwc = vcs.getVWC();
    //    Serial.print("e25");
    //    Serial.print("=");
    //    Serial.println(e25);
    //    Serial.print("ec");
    //    Serial.print("=");
    //    Serial.println(ec);
    //    Serial.print("temp");
    //    Serial.print("=");
    //    Serial.println(temp);
    //    Serial.print("vwc");
    //    Serial.print("=");
    //    Serial.println(vwc);
    
    //getting values all at one request
      float dat[4]={0,0,0,0};
      vcs.getData(dat);
      Serial.println("-----");
        Serial.print("e25");
        Serial.print("=");
        Serial.println(dat[0]);
        Serial.print("ec");
        Serial.print("=");
        Serial.println(dat[1]);
        Serial.print("temp");
        Serial.print("=");
        Serial.println(dat[2]);
        Serial.print("vwc");
        Serial.print("=");
        Serial.println(dat[3]);
      if(vwc < HT) {
        digitalWrite(relay2, HIGH);
        relay2_state = 1;
      }
      if(vwc > HT + 5) {
        digitalWrite(relay2, LOW);
        relay2_state = 0;
      }

      
///valve 3: weight
      digitalWrite(relay3, LOW);
      if (scale.is_ready()) {
        long reading = scale.read();
        Serial.print("HX711 reading: ");
        weight = reading*0.0189-50-zero;
        Serial.println(weight);
      } else {
        Serial.println("HX711 not found.");
      }   
        if (time_h ==24){
      zero = weight;
        }
        if(weight<1000) {
      digitalWrite(relay3, HIGH);
       delay(2000);
      }
       if(weight>1110) {
      digitalWrite(relay2, LOW);
     }
     
   

    
    delay(1000);
  } 

    //Thingspeak
    //Humidity
    ThingSpeak.setField(1,vwc);
    ThingSpeak.setField(2,relay2_state);
    //weight
    ThingSpeak.setField(3,weight);
    ThingSpeak.setField(4,relay3_state);
    ThingSpeak.setField(5,relay1_state);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
    Serial.println("uploaded to Thingspeak server....");
  
    client.stop();
   
    Serial.println("Waiting to upload next reading...");
    Serial.println();
    // thingspeak needs minimum 15 sec delay between updates
  
   
}
    
