// Library
#include <ESP8266WiFi.h>
#include "DHT.h"

// WiFi parameters
const char* ssid = "your-wifi-name";
const char* password = "your-wifi-pass";

// DHT11 sensor pins
#define DHTPIN 14
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Host
const char* host = "192.168.0.100";

// Thermostat control
int targetTemperature = 30;
int tolerance = 1;

void setup() {

   // Init DHT 
  dht.begin();

  // Setup
  Serial.begin(115200);

  // Connect to WiFi
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
  // Reading temperature
  int temperature = dht.readTemperature();
  Serial.print("Current temperature: ");
  Serial.println(temperature);

  // Too hot
  if (temperature > (targetTemperature + tolerance)) {
    controlHeater(0);
  }

  // Too cold   
  if (temperature < (targetTemperature - tolerance)) {
    controlHeater(1);
  }

  // Wait 10 seconds
  delay(10 * 1000);

}

void controlHeater(int state) {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/digital/5/" + String(state);

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

}
