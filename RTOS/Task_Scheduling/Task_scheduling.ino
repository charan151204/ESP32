#if CONFIG_FREERTOS_UNICORE
    static const int app_cpu = 0;
#else
    static const int app_cpu = 1;
#endif

const char msg[] = "Task scheduling ESP 32";

// To control state from 3rd task
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

void task1(void *parameter)
{
    int msg_len = strlen(msg);

    while (1)
    {
        for (int i = 0; i < msg_len; i++)
        {
            Serial.print(msg[i]);
        }
        Serial.println();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void task2(void *parameter)
{
    while (1)
    {
        Serial.print("*");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    Serial.begin(300);
    // Delay to connect the serial monitor
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println();

    Serial.print("TASK SCHEDULING IN RTOS");
    Serial.println();
    Serial.print("Setup and loop task on core ");
    Serial.print(xPortGetCoreID());
    Serial.print("with priority ");
    Serial.print(uxTaskPriorityGet(NULL));

    xTaskCreatePinnedToCore(
        task1,
        "Print Message",
        1024,
        NULL,
        1,
        &task_1,
        app_cpu);

    xTaskCreatePinnedToCore(
        task2,
        "Print *",
        1024,
        NULL,
        2,
        &task_2,
        app_cpu);

    for (int i = 0; i < 3; i++)
    {
        vTaskSuspend(task_2);
        vTaskDelay(2000 / portTICK_RATE_MS);
        vTaskResume(task_2);
        vTaskDelay(2000 / portTICK_RATE_MS);
    }

    // Delete the lower priority task
    if (task_1 != NULL)
    {
        vTaskDelete(task_1);
        task_1 = NULL;
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
}
