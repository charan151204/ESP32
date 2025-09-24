#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); 
  Serial.println("Bluetooth started. Pair with 'ESP32_BT'");
}

void loop() {
  int sensorValue = analogRead(34); 
  SerialBT.print("Sensor value: ");
  SerialBT.println(sensorValue);
  delay(1000);

  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    Serial.println("Received: " + cmd);
  }
}
