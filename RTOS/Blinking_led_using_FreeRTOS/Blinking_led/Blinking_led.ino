// Using only 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = 2;

void toggleLED_500ms(void *parameter)
{
  while(1)
  {
    digitalWrite(led, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void toggleLED_1sec(void *parameter)
{
  while(1)
  {
    digitalWrite(led, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(led, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void setup() 
{
  pinMode(2, OUTPUT);

  xTaskCreatePinnedToCore(  // To create a Task
    toggleLED_500ms,        // Function to be called
    "Toggle LED 500ms",     // Name of the task
    1024,                   // Stack size(bytes) in number for ESP32 and words for FreeRTOS
    NULL,                   // Parameter to be passed to the function
    0,                      // Task priority (0 to configMAX_PRIORITIES -1)
    NULL,                   //  Task Handle
    app_cpu);               // Run on one core

  xTaskCreatePinnedToCore(
      toggleLED_1sec,
      "Toggle LED 1sec",
      1024,
      NULL,
      0,
      NULL,
      app_cpu);
      

} 

void loop() {
  // put your main code here, to run repeatedly:

}
