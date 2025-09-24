#include <Wire.h>                     // Include I2C communication library
#include <Adafruit_GFX.h>            // Core graphics library for drawing
#include <Adafruit_SSD1306.h>        // OLED-specific driver library

#define SCREEN_WIDTH 128             // OLED display width in pixels
#define SCREEN_HEIGHT 64             // OLED display height in pixels

// Create an SSD1306 OLED display object using I2C (no reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  

void setup() {
  // Initialize the display with address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while (true);  // Halt execution if the display isn't detected
  }

  display.clearDisplay();            // Clear any previous data from the screen
  display.setTextSize(1);            // Set text size (1 = normal)
  display.setTextColor(SSD1306_WHITE); // Set text color (white on black)
  display.setCursor(0, 0);           // Set cursor to top-left corner
  display.println("HAI HELLOOO!!!"); // Print greeting message
  display.display();                 // Render the message on the OLED screen
}

void loop() {
 
}