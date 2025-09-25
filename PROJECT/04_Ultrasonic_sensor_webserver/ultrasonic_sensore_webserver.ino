#include <WiFi.h>
#include <WebServer.h>

// Ultrasonic sensor pins
#define TRIG_PIN 12
#define ECHO_PIN 14
#define THRESHOLD 20.0 // cm threshold for ENTER/EXIT

// WiFi credentials
const char *ssid = "YourSSID";
const char *password = "YourPassword";

// Web server on port 80
WebServer server(80);

long duration;
float distance_cm;

// Simple in-memory log (max 50 entries)
#define MAX_LOG 50
String logEvents[MAX_LOG];
int logIndex = 0;

// Function to log entry/exit
void logEvent(float distance)
{
    String event = String(distance, 2) + " cm";
    if (logIndex < MAX_LOG)
    {
        logEvents[logIndex++] = event;
    }
    else
    {
        // shift array if full
        for (int i = 1; i < MAX_LOG; i++)
            logEvents[i - 1] = logEvents[i];
        logEvents[MAX_LOG - 1] = event;
    }
    Serial.println("Logged: " + event);
}

// Web page handler
void handleRoot()
{
    String page = "<html><head><title>Ultrasonic Logger</title></head><body>";
    page += "<h1>ESP32 Ultrasonic Logger</h1><ul>";
    for (int i = 0; i < logIndex; i++)
    {
        page += "<li>" + logEvents[i] + "</li>";
    }
    page += "</ul></body></html>";
    server.send(200, "text/html", page);
}

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Start web server
    server.on("/", handleRoot);
    server.begin();
    Serial.println("Web server started");
}

void loop()
{
    server.handleClient();

    // Trigger ultrasonic sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance_cm = duration * 0.0343 / 2;

    if (distance_cm >= 2 && distance_cm <= 400)
    {
        logEvent(distance_cm);
    }

    delay(2000); // measure every 2 seconds
}
