#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Charan";
const char* password = "Charan12";

WebServer server(80);  // Port 80 = HTTP

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP32 Web Server!</h1>");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);   // Handle root path
  server.begin();
}

void loop() {
  server.handleClient();
}
