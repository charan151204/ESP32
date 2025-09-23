void setup() {
  Serial.begin(115200);
}

void loop() {
  int hall_sensor_value = hallRead();
  Serial.print("Hall value: ");
  Serial.println(hall_sensor_value);
  delay(1000);
}