

#include <WiFi.h>
#include "ThingSpeak.h"

// Wi-Fi credentials
const char* ssid = "Charan";
const char* password = "charan12";

// ThingSpeak settings
unsigned long channelID = 3086815;      // Replace with your channel ID
const char* writeAPIKey = "3IQMM0WRS2NRCKOU"; // Replace with your Write API Key

WiFiClient client;

// Ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 18;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi: " + WiFi.localIP().toString());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

float getDistanceCM() {
  // Send 10us pulse to trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  float distance = getDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance to ThingSpeak
  int responseCode = ThingSpeak.writeField(channelID, 1, distance, writeAPIKey);
  if (responseCode == 200) {
    Serial.println("Data uploaded successfully!");
  } else {
    Serial.println("Failed to upload. HTTP code: " + String(responseCode));
  }

  delay(20000); // ThingSpeak requires at least 15s between updates
}
