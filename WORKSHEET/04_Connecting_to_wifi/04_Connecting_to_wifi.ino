#include <WiFi.h>

const char* ssid = "Charan";      // Replace with your Wi-Fi SSID
const char* password = "password"; // Replace with your Wi-Fi password

void setup() 
{
  Serial.begin(115200);

  WiFi.begin(ssid, password); // starts to connect to wifi with the given credentials
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) // Wait till the wifi is connected
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected successfully!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Shows IP assigned by router
}

void loop() 
{
  // Nothing needed here
}
