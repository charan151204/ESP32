#define BUTTON_PIN  4   
#define LED_PIN     2   

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  
  if (buttonState == LOW) 
  {
    digitalWrite(LED_PIN, HIGH);   
    Serial.println("Button Pressed!");
  } else {
    digitalWrite(LED_PIN, LOW);    
  }

  delay(50); 
}
