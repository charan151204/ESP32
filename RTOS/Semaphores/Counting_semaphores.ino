static SemaphoreHandle_t count_sem;

void workerTask(void *parameter) {
  int id = (int)parameter;
  while (1) {
    if (xSemaphoreTake(count_sem, portMAX_DELAY))
    {
      // Critical section
      Serial.print("Task ");
      Serial.print(id);
      Serial.println(" entered (using resource)");

      vTaskDelay(2000 / portTICK_PERIOD_MS); 

      Serial.print("Task ");
      Serial.print(id);
      Serial.println(" done, releasing resource");

      xSemaphoreGive(count_sem);  // return token
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  // Create counting semaphore with max count = 3, initial count = 3
  count_sem = xSemaphoreCreateCounting(3, 3);

  // Create 5 worker tasks
  for (int i = 1; i <= 5; i++) {
    xTaskCreatePinnedToCore(
      workerTask,
      "Worker",
      1024,
      (void*)i,
      1,
      NULL,
      1
    );
  }
}

void loop() {
  // Nothing here
}
