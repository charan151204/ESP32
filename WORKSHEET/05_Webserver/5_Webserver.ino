#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "Charan";       
const char* password = "charan12"; 

WebServer server(80); // Web server on port 80

// Function to handle root URL "/"
void handleRoot() 
{
  String html = "<!DOCTYPE html><html><head><title>ESP32 Web Server</title></head><body>";
  html += "<h1>Hello from ESP32!</h1>";
  html += "<p>This is a simple webpage served by ESP32.</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html); // Send HTTP 200 response
}

void setup() 
{
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP()); // Print IP assigned by router

  // Define web server route
  server.on("/", handleRoot);

  // Start web server
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient(); // Listen for client requests
}
