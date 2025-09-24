#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4 // DHT sensor pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "Charan";
const char *password = "Charan12";

WebServer server(80);

void handleData()
{
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    String data = "Temperature: " + String(temp) + " C\n";
    data += "Humidity: " + String(hum) + " %";

    server.send(200, "text/plain", data);
}

void setup()
{
    Serial.begin(115200);
    dht.begin();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    server.on("/data", handleData);
    server.begin();
}

void loop()
{
    server.handleClient();
}
