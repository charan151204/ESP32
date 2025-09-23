#define RAIN_SENSOR 15  // Define the GPIO pin connected to the rain sensor's digital output

void setup() {
  Serial.begin(9600); // initialize serial monitor
  pinMode(RAIN_SENSOR,INPUT); // set the rain sensor pin as input
}

void loop() {
    // Read the digital signal from the rain sensor
  int RAIN_INPUT=digitalRead(RAIN_SENSOR);
  if(RAIN_INPUT == HIGH)
  {
     // If the sensor output is HIGH, that means the pad is dry (no rain)
    Serial.println("there is no rain");
  }
  else
  {
        // If the sensor output is LOW, that means the pad is wet (rain detected)
     Serial.println("there is rain");
  }

   delay(1000); //delay of 1 sec
}