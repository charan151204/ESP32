// Define joystick axis pins using preprocessor directives
#define H 12  // Horizontal axis (X-axis) 
#define Y 13  // Vertical axis (Y-axis) 

void setup() {
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set ADC attenuation to 11dB to allow voltage reading up to ~3.3V
  analogSetAttenuation(ADC_11db);
}

void loop() {
  // Read and print X-axis (horizontal) value
  Serial.print("H=");               // Print label
  Serial.println(analogRead(H));    // Read and print analog value from GPIO12

  // Read and print Y-axis (vertical) value
  Serial.print("Y=");               // Print label
  Serial.println(analogRead(Y));    // Read and print analog value from GPIO13

  // Print a separator line for clarity
  Serial.println("--------------------------------------------");

  // Wait 1 second before next reading
  delay(1000);
}