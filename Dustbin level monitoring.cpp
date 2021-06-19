#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial 
#define TRIGGER2 5
#define ECHO2    4
WiFiClient  client;


static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600;

//if Baud rate 9600 didn't work in your case then use 4800
unsigned long myChannelField = 1067056; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "FMV95MD2A1J7Y8SP"; // Your write A


TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget

SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

BlynkTimer timer;
// You should get Auth Token in the Blynk App.

char auth[] = "YVvgHBx9fIM1-yR_2XrGXXkKdIuEmrYL";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "diksha";
char pass[] = "diksha19";

unsigned int move_index = 1;

void setup() {
  
  Serial.begin (115200);
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
// timer.setInterval(5000L, checkGPS);
  
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  WiFi.mode(WIFI_STA);
  
    
  ThingSpeak.begin(client);
}

/*void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
       
  }
}*/
void loop() {

  
    if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(100);
    }
    Serial.println("\nConnected.");
  }
   
   
  while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        Serial.println("GPS Connected");//displayInfo();
        { 

  if (gps.location.isValid() ) 
  {
    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    ThingSpeak.setField(3, latitude);
        ThingSpeak.setField(4, longitude);
        ThingSpeak.writeFields(myChannelField, myWriteAPIKey); 
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
  }
  }
  }
  
  //long duration1, distance1;
  long duration2, distance2;
  
  digitalWrite(TRIGGER2, LOW); 
   
  delayMicroseconds(2); 
  
 
  digitalWrite(TRIGGER2, HIGH);
  delayMicroseconds(10); 
  
 
  digitalWrite(TRIGGER2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = (duration2/2) / 29.1;

   

   if (distance2 <= 5) {
   
    Blynk.notify("Please!! empty the dustbin");
}
 Serial.println("2 ultrasonic Centimeter:");
  Serial.println(distance2);
  Blynk.virtualWrite(V6, distance2);
  ThingSpeak.writeField(myChannelField, ChannelField, distance2, myWriteAPIKey);
  delay(100);
  Blynk.run();
  timer.run();
}
