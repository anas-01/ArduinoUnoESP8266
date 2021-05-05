// Home Automation University Dissertation Project - 19/04/2021
// Description: Home  Automation IoT system turns on light when the user is within certain distance using Ardiuno and ESP8266


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "BLYNK_AUTH_TOKEN"; // TODO - insert Blynk Token

char ssid[] = "YourNetworkName"; // TODO - insert WiFi SSID
char pass[] = "YourPassword"; // TODO - insert WiFi Password

float myLocationLat = 00.000000; // TODO - set to home geolocation latitude
float myLocationLng = 00.000000; // TODO - set to home geolocation longitude

float latitude;
float longitude;

int pinLED = 3;
bool proDebug = 1; // TODO - debugging?
int geolocation;

// automatically set parameters to a square around home
float maxLat = myLocationLat + 0.0001;
float minLat = myLocationLat - 0.0001;
float maxLng = myLocationLng + 0.0001;
float minLng = myLocationLng - 0.0001;

BLYNK_WRITE(V0) // store the geolocation to variable
{
  latitude = param[0].asFloat();
  longitude = param[1].asFloat();

  // debugging? - Consider un-commenting the lines below and test manually
    //latitude = 67.357899;
    //longitude = -8.259199;
}

void processLocation()
{
  if(latitude <= maxLat && latitude >= minLat && // check if the phone is within home's parameters
    longitude <= maxLng && longitude >= minLng)
  {
    geolocation = 1;
  }
  else
  {
    geolocation = 0;
  }
  
  if(geolocation == 1) // turn LED on if phone is in perameter
  {
    digitalWrite(pinLED, HIGH);
  }
  else
  {
    digitalWrite(pinLED, LOW);
  }
}

void setup()
{
  pinMode(pinLED, OUTPUT);
  Blynk.begin(auth, ssid, pass); // initialise Blynk

  if(proDebug)
  {
    Serial.begin(9600);
    while(!Serial) {};
    delay(1000);
    
    Serial.println("lightsOnEnter");
    delay(1000);
    Serial.println("");
    Serial.print("maxLat  "); Serial.println(maxLat, 8);
    Serial.print("minLat  "); Serial.println(minLat, 8);
    Serial.print("maxLng  "); Serial.println(maxLng, 8);
    Serial.print("minLng  "); Serial.println(minLng, 8);
    Serial.print("actual Lat  "); Serial.println(latitude, 8);
    Serial.print("actual Lng  "); Serial.println(longitude, 8);
    Serial.println("");
  }

  delay(1000);
}

void loop()
{
  Blynk.run();
  processLocation();

  if(proDebug)
  {
    Serial.print("actual Lat  "); Serial.println(latitude, 8);
    Serial.print("actual Lng  "); Serial.println(longitude, 8);
    Serial.println(geolocation);
  }
}
