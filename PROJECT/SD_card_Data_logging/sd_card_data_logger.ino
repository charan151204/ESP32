#include <SPI.h>
#include <SD.h>

// Ultrasonic pins
#define TRIG_PIN 12
#define ECHO_PIN 14
#define THRESHOLD 20.0 // cm threshold
#define CS_PIN 5       // SD card CS pin

long duration;
float distance_cm;
File myFile;

void logEvent(const char *type, float distance)
{
    myFile = SD.open("/SensorLog.txt", FILE_APPEND);
    if (myFile)
    {
        myFile.print(type);
        myFile.print(" ");
        myFile.print(distance, 2);
        myFile.println(" cm");
        myFile.close();
        Serial.println("Logged: " + String(type) + " " + String(distance, 2) + " cm");
    }
    else
    {
        Serial.println("Failed to open file for writing.");
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.println("Initializing SD card...");
    if (!SD.begin(CS_PIN))
    {
        Serial.println("SD card initialization failed!");
        while (1)
            ;
    }
    Serial.println("SD card initialized.");
}

void loop()
{
    // Trigger ultrasonic
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance_cm = duration * 0.0343 / 2;

    if (distance_cm >= 2 && distance_cm <= 400)
    {
        if (distance_cm < THRESHOLD)
        {
            logEvent("ENTER", distance_cm);
        }
        else
        {
            logEvent("EXIT", distance_cm);
        }
    }

    delay(2000);
}
