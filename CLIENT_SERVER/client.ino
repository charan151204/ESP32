#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "Charan";
const char* password = "Charan12";

const char* host = "192.168.1.45";  // Server
const int httpsPort = 443;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  WiFiClientSecure client;

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed!");
    return;
  }

  // Send GET request
  client.println("GET / HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println();

  // Read server reply
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // End of headers
    Serial.println(line);
  }
}

void loop() {}
