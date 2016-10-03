// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>
#include "DHT.h"

// WiFi parameters
const char* ssid = "Jarex_5A";
const char* password = "connect1337";

// Pin
#define DHTPIN 5

// Use DHT11 sensor
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);

// Unique ID to identify the device for cloud.arest.io
char* device_id = "9df4cr";

// Variables
float temperature;
float humidity;

void setup() {
  
  // Start Serial
  Serial.begin(115200);
  delay(10);

  // Set callback
  client.setCallback(callback);
  
  // Init DHT 
  dht.begin();

  // Give name and ID to device
  rest.set_id(device_id);
  rest.set_name("cloud_sensors");

  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
}

void loop() {
  
  // Reading temperature and humidity
  humidity = dht.readHumidity();
  
  // Read temperature as Celsius
  temperature = dht.readTemperature();

  // Connect to the cloud
  rest.handle(client);
  
}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  // Handle
  rest.handle_callback(client, topic, payload, length);

}

