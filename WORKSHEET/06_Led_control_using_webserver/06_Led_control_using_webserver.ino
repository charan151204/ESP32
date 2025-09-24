#include <WiFi.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Charan";
const char* password = "charan12";

// Web server running on port 80
WebServer server(80);

// LED pin
const int ledPin = 2;  // onboard LED

// Function to serve main page
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>button{padding:20px;font-size:20px;margin:10px;}</style></head><body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<p><a href=\"/on\"><button>LED ON</button></a></p>";
  html += "<p><a href=\"/off\"><button>LED OFF</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// Function to turn LED ON
void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/"); // Redirect to main page
  server.send(303);
}

// Function to turn LED OFF
void handleOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/"); // Redirect to main page
  server.send(303);
}

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
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // Define URL routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Handle incoming client requests
}
