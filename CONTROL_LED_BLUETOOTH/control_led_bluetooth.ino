#include "BluetoothSerial.h"

BluetoothSerial SerialBT; // Create Bluetooth Serial object

#define LED 2 // LED pin

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    SerialBT.begin("ESP32_BT"); // Bluetooth device name
    Serial.println("Bluetooth Started! Pair with ESP32_BT");
}

void loop()
{
    if (SerialBT.available())
    {
        char cmd = SerialBT.read();

        if (cmd == '1')
        { // Send '1' from App → LED ON
            digitalWrite(LED, HIGH);
            SerialBT.println("LED ON");
        }
        else if (cmd == '0')
        { // Send '0' from App → LED OFF
            digitalWrite(LED, LOW);
            SerialBT.println("LED OFF");
        }
    }
}
