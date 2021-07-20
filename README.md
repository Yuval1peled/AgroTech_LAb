# AgroTech_LAb
Liron Grosman & Yuval Peled
This is a summary of the project we have chosen to do as part of this lab. 
We were asked to come up with an irrigation system comprised of three main parts. Each one is more elaborated than the last: the first will water its plant - based on time, the second will include a sensor that will read the moisture levels in its soil and water it accordingly. Lastly, the third part of our system will weigh the plant and its soil and will water it deducting the plant's added weight.
Our whole system is built and run through Arduino esp32 board.
Complete project code, partial codes for individual parts and full project descripation is included in the attached files.



## We will build a few kinds of irrigation control systems.
   A fixed amount of water is given in fixed time intervals. \n
For this part of our system, we’ve used the following equipment and tutorials: /n 
*	1528-2003-ND Valve /n 
*	4 channel Arduino Relay /n 
•	https://media.digikey.com/pdf/Data%20Sheets/Adafruit%20PDFs/997_Web.pdf /n 
•	https://randomnerdtutorials.com/esp32-relay-module-ac-web-server/ /n 
•	Code File (included in the Github) To connect to a clock /n 

## Irrigation is actuated by a soil moisture sensor. Whenever soil moisture goes below a pre-determined threshold, irrigation faucet is opened. /n
For this part of our system, we’ve used the following equipment and tutorials: /n
•	1528-2003-ND Valve /n
•	4 channel Arduino Relay /n
•	PM-WCS-3 Sensor /n
•	https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#1 /n
•	https://github.com/tinovi/i2cArduino /n
•	https://tinovi.com/wp-content/uploads/2019/03/PM-WCS-3-I2C.pdf /n
/n
## Irrigation is actuated by the weight of the pot where the plant grows in. When the weight goes down, it means that water evaporated, and irrigation water is needed to replenish what was lost. /n
For this part of our system, we’ve used the following equipment and tutorials: /n
•	1528-2003-ND Valve /n
•	4 channel Arduino Relay /n
•	HX711-Balance-Module-With-Load-Cell /n
•	https://www.instructables.com/How-to-Interface-HX711-Balance-Module-With-Load-Ce/ /n
•	And help from our classmates /n
### On top of this we also connected our project to a private ThingSpeak server (code included in the Github). This allows us to monitor our reading from afar.

## Our modifications:
In order to operate our three valve, we needed more than one external power source, as the eps won’t run that much current through it. To solve that we connected our valves and relay to said external power supply, but each power supply outlet was strong enough to hold two valves. So, in the end we only used two power supplies for our three valves. /n
Because we use a free ThingSpeak account it can only take in readings every 15 seconds, but we wanted our systems to be more accurate than that. In order to solve that we made our system run in a loop that will read constantly the data from our sensors but will send the collected data to the server every 15 seconds. /n
HX711-Balance-Module-With-Load-Cell calibration: As the reading we got from this sensor were unreliable, we needed to calibrate it to give a more accurate read. With the help of our classmates, we created a calibration curve and equation. With those we fixed the code to give us more reliable readings. 

