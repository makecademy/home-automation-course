// Libraries
#include "DHT.h"

// Pin
#define DHTPIN 4

// Use DHT11 sensor
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {

  // Start Serial  
  Serial.begin(115200); 
 
  // Init DHT 
  dht.begin();
}

void loop() {

  // Reading temperature and humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Reading light level
  float l = analogRead(A0);
  l = l / 1023. * 100;
  
  // Display data
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Light level: "); 
  Serial.print(l);
  Serial.println(" %");
  
   // Wait a few seconds between measurements.
  delay(2000);

}
