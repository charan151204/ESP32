int Pot_value = 34; //Analog Pin

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200); //Setting the Baud rate.
  pinMode(Pot_value,INPUT); // Setting the pin to Input mode.
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int adc_value = analogRead(Pot_value); //  Reading the analog values.
  float voltage = (adc_value / 4095) * 3.3; // 12bit ADC so the value ranges from 0-4095

  Serial.print("ADC value : ");
  Serial.print(adc_value);
  Serial.println("Voltage value : ");
  Serial.print(voltage,2);
  Serial.println(" ");
}
