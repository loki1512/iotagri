
#include <Arduino.h>

#define SOIL_MOISTURE_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
}
void loop() {
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercentage = map(sensorValue, 0, 1023, 0, 100);
  Serial.print("Soil moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");
  delay(1000);
  if(moisturePercentage<50) digitalWrite(2,HIGH);
  if(moisturePercentage>50) digitalWrite(2,LOW);
  
}
