// #include <SPI.h>
// #include <SD.h>

// // Ultrasonic pins
// #define TRIG_PIN 12
// #define ECHO_PIN 14
// #define THRESHOLD 20.0 // cm threshold
// #define CS_PIN 5       // SD card CS pin

// long duration;
// float distance_cm;
// File myFile;

// void logEvent(const char *type, float distance)
// {
//     myFile = SD.open("/SensorLog.txt", FILE_APPEND);
//     if (myFile)
//     {
//         myFile.print(type);
//         myFile.print(" ");
//         myFile.print(distance, 2);
//         myFile.println(" cm");
//         myFile.close();
//         Serial.println("Logged: " + String(type) + " " + String(distance, 2) + " cm");
//     }
//     else
//     {
//         Serial.println("Failed to open file for writing.");
//     }
// }

// void setup()
// {
//     Serial.begin(115200);
//     pinMode(TRIG_PIN, OUTPUT);
//     pinMode(ECHO_PIN, INPUT);

//     Serial.println("Initializing SD card...");
//     if (!SD.begin(CS_PIN))
//     {
//         Serial.println("SD card initialization failed!");
//         while (1)
//             ;
//     }
//     Serial.println("SD card initialized.");
// }

// void loop()
// {
//     // Trigger ultrasonic
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

// SD Card SPI pins
#define SD_CS 5

long duration;
float distance_cm;

// --- SD card SPI commands ---
#define CMD0  0x40
#define CMD17 0x51
#define CMD24 0x58
#define CMD55 0x77
#define ACMD41 0x69

// --- State tracking ---
bool objectInside = false; // true if object is currently "inside" threshold

// Function to send a command to SD card
uint8_t sdCommand(uint8_t cmd, uint32_t arg) {
  digitalWrite(SD_CS, LOW);
  SPI.transfer(cmd);
  SPI.transfer(arg >> 24);
  SPI.transfer(arg >> 16);
  SPI.transfer(arg >> 8);
  SPI.transfer(arg & 0xFF);
  SPI.transfer(0x95); // CRC for CMD0, ignored for others
  uint8_t response;
  for (int i = 0; i < 8; i++) {
    response = SPI.transfer(0xFF);
    if (response != 0xFF) break;
  }
  digitalWrite(SD_CS, HIGH);
  SPI.transfer(0xFF); // extra clock
  return response;
}

void sdInit() {
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(400000, MSBFIRST, SPI_MODE0));

  // Send 80 clocks with CS high
  for (int i = 0; i < 10; i++) SPI.transfer(0xFF);

  uint8_t r = sdCommand(CMD0, 0);
  if (r != 1) Serial.println("CMD0 failed");

  // Send ACMD41 until card is ready
  while (sdCommand(CMD55, 0) != 1);
  while (sdCommand(ACMD41, 0) != 0);

  Serial.println("SD card initialized (SPI).");
}

// Write a single 512-byte block to SD
bool sdWriteBlock(uint32_t blockAddr, const uint8_t *data) {
  digitalWrite(SD_CS, LOW);
  sdCommand(CMD24, blockAddr * 512);
  SPI.transfer(0xFE); // start block token
  for (int i = 0; i < 512; i++) SPI.transfer(data[i]);
  SPI.transfer(0xFF); // dummy CRC
  SPI.transfer(0xFF);
  digitalWrite(SD_CS, HIGH);
  SPI.transfer(0xFF);
  return true;
}

uint32_t flashAddr = 0;
void logEvent(const char* type, float distance) {
  uint8_t buf[512];
  memset(buf, 0, 512);
  snprintf((char*)buf, 512, "%s %.2f cm", type, distance);
  sdWriteBlock(flashAddr, buf);
  flashAddr++; // move to next block if needed
  Serial.println("Logged: " + String(type) + " " + String(distance));
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  sdInit();
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
    // One-time event logic
    if (!objectInside && distance_cm < THRESHOLD) {
      logEvent("ENTER", distance_cm);
      objectInside = true; // mark inside
    } 
    else if (objectInside && distance_cm >= THRESHOLD) {
      logEvent("EXIT", distance_cm);
      objectInside = false; // mark outside
    }
  } else {
    Serial.println("Out of range");
  }

  delay(200); // small delay to prevent multiple logs
}

