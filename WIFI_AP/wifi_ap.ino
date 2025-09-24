#include <WiFi.h>  // Include WiFi library for ESP32

void setup() {
  Serial.begin(9600);       // Start serial communication at 9600 baud
  delay(3000);              // Wait for 3 seconds before starting

  Serial.println("START");

  // Start Wi-Fi in Access Point (AP) mode with SSID and password
  WiFi.softAP("Wifi Network", "12345678");

  // Print the IP address assigned to the access point
  Serial.println("The IP of the access Point is : ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Print the number of devices connected to the access point
  Serial.println("The number of connected station: ");
  Serial.println(WiFi.softAPgetStationNum());

  delay(5000);  // Wait for 5 seconds before checking again
}