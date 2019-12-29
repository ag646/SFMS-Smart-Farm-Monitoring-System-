#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 // Create Amplitude Shift Keying Object
RH_ASK rf_driver;
DHT dht(DHTPIN, DHTTYPE);
int resval = 0; // holds the value
int respin = A5; // sensor pin used
int cm;
const int soil_sensor = A0;  // Analog input pin that the soil moisture sensor is attached to
int soilValue = 0; 

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  // Initialize ASK Object
    rf_driver.init();
  //Define inputs and outputs
  pinMode(6,OUTPUT); // Water Level
  pinMode(5,OUTPUT); // Soil Moisture
  pinMode(3,OUTPUT); // DHT11
  dht.begin();
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
  
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
  if (resval<=100)
  { 
    cm=0;
  } 
  else if (resval>100 && resval<=300)
  { 
    cm=1; 
  } 
  else if (resval>300 && resval<=330)
  { 
    cm=2;  
  } 
  else if (resval>330)
  {
    cm=3;
  }
  if (cm<=1) 
  {
    digitalWrite(6,HIGH);
  }
  delay(100);
  soilValue = analogRead(soil_sensor);            
  soilValue = (soilValue/1023) * 100;
  Serial.print("Moisture Value = " );                       
  Serial.println(soilValue);    
  if (soilValue==0) {
    digitalWrite(5,HIGH);
  }
  delay(100);
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hi = dht.computeHeatIndex(f, h);
  if (t>=30){
    digitalWrite(3,HIGH);
  }
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  //const char *msg_ = "Start";
  const char msg[10];
  const char msg1[10];
  const char msg2[10];
  
  dtostrf(cm,4,4,msg);
  dtostrf(soilValue,4,4,msg1);
  dtostrf(t,4,4,msg2);
  //rf_driver.send((uint8_t *)msg_, strlen(msg_));
  rf_driver.send((uint8_t *)msg, strlen(msg));
  delay(100);
  rf_driver.send((uint8_t *)msg1, strlen(msg1));
  delay(100);
  rf_driver.send((uint8_t *)msg2, strlen(msg2));
  delay(100);            
}
