#define PIR_SENSOR 25
#define LED 12



void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_SENSOR,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int PIR_OUTPUT=digitalRead(PIR_SENSOR);

  if (PIR_OUTPUT == HIGH)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  delay(100);

}