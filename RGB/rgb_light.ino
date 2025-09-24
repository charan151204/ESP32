// Define GPIO pins for Red, Green, and Blue channels of the RGB LED
#define R 12  // Red pin connected to GPIO 12
#define G 13  // Green pin connected to GPIO 13
#define B 14  // Blue pin connected to GPIO 14

void setup() {
  // Set RGB pins as output so they can control LED brightness or ON/OFF
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  // --- Turn ON RED, turn OFF Green and Blue ---
  digitalWrite(R, HIGH);  // Red ON
  digitalWrite(G, LOW);   // Green OFF
  digitalWrite(B, LOW);   // Blue OFF
  delay(3000);            // Wait 3 seconds

  // --- Turn ON GREEN, turn OFF Red and Blue ---
  digitalWrite(R, LOW);   // Red OFF
  digitalWrite(G, HIGH);  // Green ON
  digitalWrite(B, LOW);   // Blue OFF
  delay(3000);            // Wait 3 seconds

  // --- Turn ON BLUE, turn OFF Red and Green ---
  digitalWrite(R, LOW);   // Red OFF
  digitalWrite(G, LOW);   // Green OFF
  digitalWrite(B, HIGH);  // Blue ON
  delay(3000);            // Wait 3 seconds
}