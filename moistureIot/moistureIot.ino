#define BLYNK_TEMPLATE_ID "TMPLGonwzQTu"
#define BLYNK_TEMPLATE_NAME "SMART IRRIGATION USING IOT"
#define BLYNK_AUTH_TOKEN "NHdtZMbO6407cHXzn0pNK67HGGVLfKaL"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <DHT.h>


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include "ACS712.h
//ACS712 sensor(ACS712_30A,A0);
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Don't connect";
char pass[] = "123456789";

DHT dht(D2, DHT11);    // Initialize DHT sensor
void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  pinMode(4,OUTPUT);
  pinMode(0,INPUT);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  
}
void loop()
{
  
  float soilMoistureMapped=moist();
  Blynk.virtualWrite(V5, soilMoistureMapped);              // Send mapped soil moisture value to Blynk dashboard
  delay(1000);   // Wait for 1 second before taking next reading
  Blynk.run();   // Update Blynk dashboard
  float temperature = dht.readTemperature();    // Read temperature from DHT11 sensor
  float humidity = dht.readHumidity();
  Blynk.virtualWrite(V4, temperature);
  Serial.println(temperature); 
  Blynk.virtualWrite(V2, humidity);
  if(soilMoistureMapped<20)
  {
    Blynk.virtualWrite(V0,1);
    digitalWrite(3,HIGH);
  }
  if(soilMoistureMapped>20)
  {
    Blynk.virtualWrite(V0,0);
    digitalWrite(3,HIGH);
  }
  /*else
  {
    Blynk.virtualWrite(V0,LOW);
    digitalWrite(D3,LOW);
  }*/
  //Serial.println(V4);
  //Serial.println(V5); 
}


float moist()
{
  int sensorValue = analogRead(A0);
  int moisturePercentage = map(sensorValue, 0, 1023, 100, 0);
  return moisturePercentage;
}
