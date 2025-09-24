#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "Charan";
const char *password = "charan12";

WebServer server(80);

#define LED 2

void handleRoot() { server.send(200, "text/plain", "ESP32 running!"); }
void handleLEDOn()
{
    digitalWrite(LED, HIGH);
    server.send(200, "text/plain", "LED ON");
}
void handleLEDOff()
{
    digitalWrite(LED, LOW);
    server.send(200, "text/plain", "LED OFF");
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/ledon", handleLEDOn);
    server.on("/ledoff", handleLEDOff);
    server.begin();
}

void loop()
{
    server.handleClient();
}
