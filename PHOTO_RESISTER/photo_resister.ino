#define PHOTODIODE_PIN 34 

void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(PHOTODIODE_PIN);  
  Serial.print("Light level: ");
  Serial.println(value);
  delay(200);
}
