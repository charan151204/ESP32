// Using only 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = 2;

void toggleLED_500ms(void *parameter)
{
  while (1)
  {
    digitalWrite(led_pin, HIGH);
    Serial.println("Task 1 (500ms ON)");
    vTaskDelay(500 / portTICK_PERIOD_MS);

    digitalWrite(led_pin, LOW);
    Serial.println("Task 1 (500ms OFF)");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void toggleLED_1sec(void *parameter)
{
  while (1)
  {
    digitalWrite(led_pin, HIGH);
    Serial.println("Task 2 (1s ON)");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    digitalWrite(led_pin, LOW);
    Serial.println("Task 2 (1s OFF)");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  // Task 1: 500ms blink
  xTaskCreatePinnedToCore(
      toggleLED_500ms,
      "Toggle LED 500ms",
      2048,
      NULL,
      1,     // priority 1
      NULL,
      app_cpu);

  // Task 2: 1s blink
  xTaskCreatePinnedToCore(
      toggleLED_1sec,
      "Toggle LED 1sec",
      2048,
      NULL,
      1,     // same priority
      NULL,
      app_cpu);
}

void loop()
{
  // Nothing here, tasks run independently
}
