int ledpin = 2;

void setup()
{
  Serial.begin(115200);
  pinMode(ledpin, OUTPUT);
}

void loop()
{
    digitalWrite(ledpin, HIGH);
    Serial.println("LED : ON");
    delay(1000);
    digitalWrite(ledpin, LOW);
    Serial.println("LED : OFF");
    delay(1000);

}