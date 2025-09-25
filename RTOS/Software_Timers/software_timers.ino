#if CONFIG_FREERTOS_UNICORE
static const int app_cpu = 0;
#else
static const int app_cpu = 1;
#endif

static TimerHandle_t one_shot_timer = NULL;
static TimerHandle_t auto_reload_timer = NULL;

//Timer callback function
void TimerCallBack(TimerHandle_t xTimer)
{
  if((uint32_t)pvTimerGetTimerID(xTimer) == 0)
  {
    Serial.println("One shot timer expired");
  }

    if((uint32_t)pvTimerGetTimerID(xTimer) == 1)
  {
    Serial.println("Autoreload timer expired");
  }
}

void setup()
{
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("FreeRTOS Timer");

  one_shot_timer = xTimerCreate(
    "One shot Timer",
    2000 / portTICK_PERIOD_MS,
    pdFALSE,
    (void *) 0,
    TimerCallBack);

  auto_reload_timer = xTimerCreate(
    "AutoReload Timer",             //Timer name
    1000 / portTICK_PERIOD_MS,      //Period 
    pdTRUE,                         // The timer will execute again after expiring
    (void *) 1,                     // Timer Id
    TimerCallBack);                 //Callback function

    if(one_shot_timer == NULL || auto_reload_timer == NULL)
    {
      Serial.println("Could not create the Timer");
    }
    else
    {

      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.println("Starting Timer..");

      // Start the timer (max time if queue is full)
      xTimerStart(one_shot_timer, portMAX_DELAY);
      xTimerStart(auto_reload_timer, portMAX_DELAY);
    }

  vTaskDelete(NULL);
}

void loop()
{

}