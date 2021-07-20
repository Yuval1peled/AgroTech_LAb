#include "HX711.h"
 
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 22;
const int LOADCELL_SCK_PIN = 23;
float zero;
HX711 scale;
 
void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(1000);
  if (scale.is_ready()) {
    long reading = scale.read();
    //Serial.print("HX711 reading: ");
    zero = reading*0.0189-157017;
  } else {
    Serial.println("HX711 not found.");
  }
}
 
void loop() {
  if (scale.is_ready()) {
    long reading = scale.read();
    //Serial.print("HX711 reading: ");
    Serial.println(reading*0.0189-157017-zero);
  } else {
    Serial.println("HX711 not found.");
  }
delay(100);
}
