const int ledPin =12;       // the PWM pin the LED is attached to
const int freq = 5000;    // freq = 5 khz
const int resolution = 8;    // 8 bit resolution

void setup() {
 ledcAttach(ledPin, freq, resolution); // Attach LED pin to PWM channel with specified freq and resolution
}

void loop() {
  // Increase brightness
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) 
  {
    ledcWrite(ledPin, dutyCycle);  // Set PWM duty cycle
    delay(15);                     // Small delay for smooth fade
  }

  // Decrease brightness
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) 
  {
    ledcWrite(ledPin, dutyCycle);  // Set PWM duty cycle
    delay(15);                     // Small delay for smooth fade
  }
}
  