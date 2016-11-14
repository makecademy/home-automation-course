// Library
#include <ESP8266WiFi.h>

// WiFi parameters
const char* ssid = "your-wifi-name";
const char* password = "your-wifi-pass";

// Host
const char* host = "192.168.0.103";

// Button pin
const int buttonPin = 5;

// Variables
int buttonState;
int lastButtonState = LOW;

// Debounce time constants
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {

  // Setup
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);

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
  // Read the state of the button
  int reading = digitalRead(buttonPin);

  // If the button state changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // If the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // Only send command if state is HIGH
      if (buttonState == HIGH) {
        Serial.println(buttonState);
        ringBell();
      }
    }
  }

  // Save the reading
  lastButtonState = reading;
}

void ringBell() {

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/bell";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

}
