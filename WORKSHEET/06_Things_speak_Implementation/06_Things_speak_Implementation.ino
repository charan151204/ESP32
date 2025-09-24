#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Charan";
const char* password = "charan12";

// ThingSpeak settings
const char* apiKey = "469RV5R8RTREIBM3"; // Write API Key
const char* server = "http://api.thingspeak.com/update";

// LED pin
const int ledPin = 2; // onboard LED for ESP32

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  static bool ledStatus = false;

  // Toggle LED
  ledStatus = !ledStatus;
  digitalWrite(ledPin, ledStatus ? HIGH : LOW);
  Serial.print("LED is now: ");
  Serial.println(ledStatus ? "ON" : "OFF");

  // Push status to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(ledStatus ? 1 : 0);
    
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("ThingSpeak Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }

  delay(5000); // Update every 5 seconds
}
