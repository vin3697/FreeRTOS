



 
#include <Arduino_FreeRTOS.h>
#include "semphr.h"





#define RED     8
#define GREEN   6
#define BLUE    3



typedef int TaskProfiler;
TaskProfiler REDTaskProfiler;
TaskProfiler GREENTaskProfiler;
TaskProfiler BLUETaskProfiler;

// Semaphore Handle
SemaphoreHandle_t s_BinarySemaphore;

//milli seconds to ticks
TickType_t delaymsTotick = pdMS_TO_TICKS(5000);

void setup() {
  // put your setup code here, to run once:

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  s_BinarySemaphore = xSemaphoreCreateBinary();


  xTaskCreate(REDTask, "Red LED Controller", 100, NULL, 1, NULL);
  xTaskCreate(GREENTask, "Green LED Controller", 100, NULL, 1, NULL);
  xTaskCreate(BLUETask, "Blue LED Controller", 100, NULL, 1, NULL);

}


void REDTask(void *pvParameters){

  xSemaphoreGive(s_BinarySemaphore);
  while(1){
      vTaskDelay(delaymsTotick);
      xSemaphoreTake(s_BinarySemaphore, delaymsTotick);
      digitalWrite(RED, digitalRead(RED)^1);
      xSemaphoreGive(s_BinarySemaphore);
      //vTaskDelay(delaymsTotick);
  }

}

void GREENTask(void *pvParameters){


  while(1){
      xSemaphoreTake(s_BinarySemaphore, delaymsTotick);
      digitalWrite(GREEN, digitalRead(GREEN)^1);
      xSemaphoreGive(s_BinarySemaphore);
      //vTaskDelay(delaymsTotick);
  }


}

void BLUETask(void *pvParameters){


  while(1){
      xSemaphoreTake(s_BinarySemaphore, delaymsTotick);
      digitalWrite(BLUE, digitalRead(BLUE)^1);
      xSemaphoreGive(s_BinarySemaphore);
      //vTaskDelay(delaymsTotick);
  }


}






void loop() {
  // put your main code here, to run repeatedly:

}











































