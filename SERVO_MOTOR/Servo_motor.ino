#include<ESP32Servo.h>

Servo myservo;

#define servopin 5 //set pin 5 as servo motor input


void setup() {
  // put your setup code here, to run once:
  myservo.setPeriodHertz(50); //set frequency to 50hz
  myservo.attach(servopin, 500, 2400); 

}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(0); // move 0 degree
  delay(1000);
  myservo.write(90); // move 90 degree
  delay(1000);
  myservo.write(180); // move 180 degree
  delay(1000);

}