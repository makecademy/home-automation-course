// Pins
int motorPinPlus = 14;
int motorPinMinus = 15;

// Libraries
#include <ESP8266WiFi.h>
#include <SHT1x.h>

// Humidity threshold
float threshold = 70.00;
float tolerance = 1.00;

// Pins
#define dataPin  4
#define clockPin 5

// Variables to be measured
float temperature;
float humidity;

// Create instance for the sensor
SHT1x sht1x(dataPin, clockPin);

void setup() {

  pinMode(motorPinPlus, OUTPUT);
  pinMode(motorPinMinus, OUTPUT);
    
  Serial.begin(115200);
  
}


void loop() {

  // Read values from the sensor
  temperature = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Check humidity data
  if (humidity < threshold - tolerance) {

   // Activate pump
   setMotor(true);
    
  }
  if (humidity > threshold + tolerance) {

    // Stop pump
    setMotor(false);

  }
 
}

// Function to control the motor
void setMotor(boolean state){
  if (state) {
    digitalWrite(motorPinPlus, true);
    digitalWrite(motorPinMinus, false);
  }
  else {
    digitalWrite(motorPinPlus, false);
    digitalWrite(motorPinMinus, false);
  }
}

