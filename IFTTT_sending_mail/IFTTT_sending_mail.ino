#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "Charan";
const char* password = "charan12";

// Replace with your IFTTT webhook URL
const char* IFTTT_URL = "YOUR_IFTTT_KEY";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    Serial.printf("Temp: %.1f °C, Hum: %.1f %%\n", temp, hum);

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(IFTTT_URL) + "?value1=" + String(temp) + "&value2=" + String(hum);
      http.begin(url);
      int httpCode = http.GET();  // Send GET request
      if (httpCode > 0) {
        Serial.println("Email sent via IFTTT!");
      } else {
        Serial.println("Error sending email");
      }
      http.end();
    }
  }

  delay(60000); // Send every 60 seconds
}
