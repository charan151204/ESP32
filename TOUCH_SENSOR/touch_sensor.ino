#define TOUCH_PIN 4  
#define LED_PIN 2      

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN); 
  Serial.println(touchValue);
  
  if (touchValue < 40) 
  {   
    digitalWrite(LED_PIN, HIGH);
  } 
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}
