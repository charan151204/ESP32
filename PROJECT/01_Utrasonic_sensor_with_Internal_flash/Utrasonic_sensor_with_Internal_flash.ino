#include <Arduino.h>
#include <Preferences.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define THRESHOLD 20.0  // cm threshold for ENTER/EXIT
#define MAX_EVENTS 50

Preferences prefs;

enum ObjectState { OUTSIDE,
                   INSIDE };
ObjectState lastState = OUTSIDE;

int eventCount = 0;
long duration;
float distance;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  prefs.begin("ultrasonic", false);

  // Load previous events
  eventCount = prefs.getInt("eventCount", 0);
  Serial.printf("Previous event count: %d\n", eventCount);

  if (eventCount > 0) {
    for (int i = 1; i <= eventCount; i++) {
      String key = "event" + String(i);
      String value = prefs.getString(key.c_str(), "");
      if (value != "") Serial.println(value);
    }
  } else {
    Serial.println("No previous events logged.");
  }

  Serial.println("Type 'c' and press Enter to clear all logs.");
}

void logEvent(const char* eventName, float dist) {
  eventCount++;
  if (eventCount > MAX_EVENTS) 
      eventCount = 1;  // overwrite oldest

  prefs.putInt("eventCount", eventCount);

  String key = "event" + String(eventCount);
  String value = String(eventName) + " at " + String(dist, 2) + " cm";
  prefs.putString(key.c_str(), value);

  Serial.println("Logged: " + value);
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  if (duration == 0) return 0.0;
  float dist = (duration * 0.0343) / 2;

  if (dist > 400.0) dist = 0.0;  // clamp invalid readings
  return dist;
}

void loop() {
  // --- Check for Serial command ---
  if (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == 'c' || ch == 'C') {
      prefs.clear();  // clear all NVS logs
      eventCount = 0;
      Serial.println("All logs cleared!");
    }
  }

  // --- Ultrasonic logging ---
  distance = readDistance();
  ObjectState currentState = (distance <= THRESHOLD && distance > 0) ? INSIDE : OUTSIDE;

  if (currentState != lastState) {
    if (currentState == INSIDE) 
      logEvent("ENTER", distance);
    else 
      logEvent("EXIT", distance);

    lastState = currentState;
  }

  delay(200);
}
