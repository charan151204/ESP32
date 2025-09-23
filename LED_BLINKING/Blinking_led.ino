int Led = 12;

void setup() {
  Serial.begin(115200);
  Serial.println("LED STATUS");
  pinMode(12, OUTPUT);  // GPIO2
}

void loop() {
  digitalWrite(12, LOW);
  Serial.begin("LED OFF")
  delay(500);
  digitalWrite(12, HIGH);
  Serial.begin("LED OFF");
  delay(500);
}
