//gkapsid
//worked 06/04/2022
//needs modification according https://docs.blynk.io/en/blynk.cloud/troubleshooting
// Controls an ESP8266 output


/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V0
    Value Display widget attached to V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your_SSID";
char pass[] = "your_PSSWD";
bool debug = false;
#define DHTPIN 14          // What digital pin we're connected to

float sensorData;

BlynkTimer timer;



BLYNK_WRITE(V3) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(D5,HIGH);  // Set digital pin 2 HIGH
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(D5,LOW);  // Set digital pin 2 LOW    
  }
}

void myTimerEvent()
{
  sensorData = analogRead(A0);
  Blynk.virtualWrite(V5, sensorData);
}


void setup()
{
  // Debug console
  if (debug) {
    Serial.begin(115200);
    Serial.println("Initializing...");
  }
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "fra1.blynk.cloud", 80); // gkapsid: here is specified a custom service in case of Invalid auth key error
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(D5, OUTPUT);
    timer.setInterval(1000L, myTimerEvent);
  
}

void loop()

{
   
  if (debug) {
    Serial.println("Running Blynk");
  }
  Blynk.run();

  if (debug) {
    Serial.println("Running timer");
  }
  timer.run();

}
