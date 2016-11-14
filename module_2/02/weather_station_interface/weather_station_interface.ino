// WiFi Weather Station

// Required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>
#include "DHT.h"

// Create aREST instance
aREST_UI rest = aREST_UI();

// Pin
#define DHTPIN 4

// Use DHT11 sensor
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// WiFi parameters
const char* ssid = "wifi-name";
const char* password = "wifi-password";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
float temperature;
float humidity;
float light;

void setup() {

  // Start Serial
  Serial.begin(115200);
  delay(10);

  // Init DHT
  dht.begin();

  // Expose variables
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);
  rest.variable("light", &light);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");

  // Displays
  rest.label("temperature");
  rest.label("humidity");
  rest.label("light");

  // Connect to WiFi network
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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Reading temperature and humidity
  humidity = dht.readHumidity();
  // Read temperature as Celsius
  temperature = dht.readTemperature();

  // Reading light level
//  light = analogRead(A0);
//  light = light / 1023. * 100;
    light = 23.12;

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}
