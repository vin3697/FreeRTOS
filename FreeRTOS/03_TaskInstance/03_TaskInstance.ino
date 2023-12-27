
#include <Arduino_FreeRTOS.h>
#define RED   8
#define GREEN 6
#define BLUE  3 

typedef int TaskProfiler; // profiler are useful to check whether the thread/task is dead or alive!

TaskProfiler RedLEDProfiler;
TaskProfiler GreenLEDProfiler;
TaskProfiler BlueLEDProfiler;


void setup() {
  // put your setup code here, to run once:
  uint16_t *redptr   = (uint16_t *)RED;
  uint16_t *greenptr = (uint16_t *)GREEN;
  uint16_t *blueptr  = (uint16_t *)BLUE;

  xTaskCreate(LEDController, "LED controller", 100, (void *)redptr, 3, NULL);
  xTaskCreate(LEDController, "LED controller", 100, (void *)greenptr, 3, NULL);
  xTaskCreate(LEDController, "LED controller", 100, (void *)blueptr, 3, NULL);  
}


void LEDController(void *pvparameter){

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);


  while(1){
    digitalWrite(pvparameter, digitalRead(pvparameter)^1);
    delay(500);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
