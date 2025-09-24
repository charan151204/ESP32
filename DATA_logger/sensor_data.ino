#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "Charan";
const char *password = "charan12";

WebServer server(80);

// CSV stored in memory
String csvData = "Time,Temperature,Humidity\n";

void handleCSV()
{
    server.send(200, "text/csv", csvData); // Send CSV to PC
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

    server.on("/data.csv", handleCSV); // Handle CSV request
    server.begin();
}

void loop()
{
    server.handleClient();

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    unsigned long t = millis() / 1000;

    if (!isnan(temp) && !isnan(hum))
    {
        String line = String(t) + "," + String(temp) + "," + String(hum);
        csvData += line + "\n";
        Serial.println(line);
    }

    // Limit CSV size to avoid ESP32 RAM overflow
    if (csvData.length() > 20000)
    {
        csvData = "Time,Temperature,Humidity\n";
    }

    delay(5000); // Read every 5 sec
}
