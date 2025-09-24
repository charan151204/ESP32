#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define SENSOR_PIN 34     

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensorValue = 0;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) 
  {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("OLED & Relay Demo");
  display.display();
  delay(2000);
}

void loop() 
{
  sensorValue = analogRead(SENSOR_PIN);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Sensor Reading:");
  
  display.setTextSize(2);
  display.setCursor(0,15);
  display.println(sensorValue);
  display.display();

  delay(1000); 
