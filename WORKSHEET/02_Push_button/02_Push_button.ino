int BUTTON_PIN = 4;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) 
  {   
    Serial.println("BUTTON STATE : ON");
  } 
  else 
  {
    Serial.println("BUTTON STATE : OFF");
  }

  delay(50); 
}

