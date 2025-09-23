#define RELAY 25 // PIN 25 is connected to Relay

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY,OUTPUT); // Configure PIN 25 as output

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY,HIGH); // write high on Relay pin(turn on relay)
  delay(1000); // delay of 1 sec
  digitalWrite(RELAY,LOW); // write low on Relay pin(turn off relay)
   delay(1000); // dlay of 1 sec

}