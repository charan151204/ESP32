// #include <SPI.h>
// #include <Adafruit_SPIFlash.h>
// #include <Adafruit_FlashTransport_SPI.h>

// // Ultrasonic pins
// #define TRIG_PIN 12
// #define ECHO_PIN 14
// #define THRESHOLD 20.0 // cm threshold

// // W25QXX SPI pins
// #define FLASH_CS 21

// SPIFlash flash(FLASH_CS);
// Adafruit_FlashTransport_SPI flashTransport(FLASH_CS, SPI);

// long duration;
// float distance_cm;
// uint32_t flashAddr = 0; // starting address

// void setup()
// {
//     Serial.begin(115200);
//     pinMode(TRIG_PIN, OUTPUT);
//     pinMode(ECHO_PIN, INPUT);

//     // Initialize flash
//     if (!flash.begin())
//     {
//         Serial.println("Flash init failed!");
//         while (1)
//             ;
//     }
//     Serial.println("Flash initialized!");
// }

// void logEvent(const char *type, float distance)
// {
//     // Prepare 32-byte buffer for flash
//     char buf[32];
//     snprintf(buf, sizeof(buf), "%s %.2f cm", type, distance);

//     // Ensure 4096-byte sector erase before writing if needed
//     if ((flashAddr % 4096) == 0)
//     {
//         flash.eraseSector(flashAddr / 4096);
//     }

//     // Write buffer
//     flash.writeBuffer(flashAddr, (uint8_t *)buf, sizeof(buf));
//     flashAddr += sizeof(buf);

//     Serial.println("Logged: " + String(buf));
// }

// void loop()
// {
//     // Trigger ultrasonic sensor
//     digitalWrite(TRIG_PIN, LOW);
//     delayMicroseconds(2);
//     digitalWrite(TRIG_PIN, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TRIG_PIN, LOW);

//     duration = pulseIn(ECHO_PIN, HIGH);
//     distance_cm = duration * 0.0343 / 2;

//     if (distance_cm >= 2 && distance_cm <= 400)
//     {
//         if (distance_cm < THRESHOLD)
//         {
//             logEvent("ENTER", distance_cm);
//         }
//         else
//         {
//             logEvent("EXIT", distance_cm);
//         }
//     }

//     delay(2000);
// }


#include <SPI.h>

// HC-SR04 pins
#define TRIG_PIN 12
#define ECHO_PIN 14
#define THRESHOLD 20.0

// W25QXX SPI pins
#define FLASH_CS 21

long duration;
float distance_cm;

// --- W25QXX commands ---
#define CMD_WRITE_ENABLE 0x06
#define CMD_PAGE_PROGRAM 0x02
#define CMD_READ_DATA    0x03
#define CMD_SECTOR_ERASE 0x20
#define CMD_READ_STATUS  0x05

uint32_t flashAddr = 0;

void writeEnable() {
  digitalWrite(FLASH_CS, LOW);
  SPI.transfer(CMD_WRITE_ENABLE);
  digitalWrite(FLASH_CS, HIGH);
}

void eraseSector(uint32_t addr) {
  writeEnable();
  digitalWrite(FLASH_CS, LOW);
  SPI.transfer(CMD_SECTOR_ERASE);
  SPI.transfer((addr >> 16) & 0xFF);
  SPI.transfer((addr >> 8) & 0xFF);
  SPI.transfer(addr & 0xFF);
  digitalWrite(FLASH_CS, HIGH);
  delay(50); // wait for erase
}

void writePage(uint32_t addr, uint8_t *data, uint16_t len) {
  writeEnable();
  digitalWrite(FLASH_CS, LOW);
  SPI.transfer(CMD_PAGE_PROGRAM);
  SPI.transfer((addr >> 16) & 0xFF);
  SPI.transfer((addr >> 8) & 0xFF);
  SPI.transfer(addr & 0xFF);
  for (int i = 0; i < len; i++) SPI.transfer(data[i]);
  digitalWrite(FLASH_CS, HIGH);
  delay(10);
}

void logEvent(const char* type, float distance) {
  char buf[32];
  snprintf(buf, sizeof(buf), "%s %.2f cm", type, distance);

  if ((flashAddr % 4096) == 0) eraseSector(flashAddr);

  writePage(flashAddr, (uint8_t*)buf, sizeof(buf));
  flashAddr += sizeof(buf);

  Serial.println("Logged: " + String(buf));
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(FLASH_CS, OUTPUT);
  digitalWrite(FLASH_CS, HIGH);

  SPI.begin(); // SCK=18, MOSI=19, MISO=23 by default

  Serial.println("Setup done!");
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration * 0.0343 / 2;

  if (distance_cm >= 2 && distance_cm <= 400) {
    if (distance_cm < THRESHOLD) logEvent("ENTER", distance_cm);
    else logEvent("EXIT", distance_cm);
  }

  delay(2000);
}
