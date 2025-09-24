// Using only 1 core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static int shared_var = 0;
static SemaphoreHandle_t mutex;

void incTask(void *parameters)
{
    int local_var;

    while (1)
    {
        // Take mutex prior to critical section
        if (xSemaphoreTake(mutex, 0) == pdTRUE)
        {
            local_var = shared_var;
            local_var++;
            vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
            shared_var = local_var;
            xSemaphoreGive(mutex);
            Serial.println(shared_var);
        }
    }
}
void setup()
{
    mutex = xSemaphoreCreateMutex();
    Serial.begin(115200);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println();
    Serial.println("----------Race Condition---------");
    // put your setup code here, to run once:

    xTaskCreatePinnedToCore(
        incTask,
        "Increment count",
        1024,
        NULL,
        1,
        NULL,
        app_cpu);

    vTaskDelete(NULL);
}

void loop()
{
    // put your main code here, to run repeatedly:
}
