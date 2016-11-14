// Library
#include <SHT1x.h>

// Pins
#define dataPin  4
#define clockPin 5

// Create instance for the sensor
SHT1x sht1x(dataPin, clockPin);

void setup()
{
   Serial.begin(115200); // Open serial connection to report values to host
   Serial.println("Starting up");
}

void loop()
{
  // Variables
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();

  // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c, DEC);
  Serial.print("C / ");
  Serial.print(temp_f, DEC);
  Serial.print("F. Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Wait 2 seconds
  delay(2000);
}
