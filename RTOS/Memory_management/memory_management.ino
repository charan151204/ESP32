#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

void testTask(void *parameter)
{
  int a = 1;
  int b[100];

  while(1)
  {
    for(int i = 0; i < 100; i++)
    {
      b[i] = a + 1;
    }
    Serial.println(b[0]);

    //To print how much stack memory is remaining
    Serial.print("High water mark (words) : ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    //Total avalilable heap
    Serial.print("Heap before malloc (bytes) : ");
    Serial.println(xPortGetFreeHeapSize());
  }
}


void setup()
{
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(testTask,
    "Test Task",
    1024, //stack size it requires 1200 bytes so change it to 1500
    NULL,
    1,
    NULL,
    app_cpu
  );

  vTaskDelete(NULL);
}

void loop()
{

}