







#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED     8
#define GREEN   6
#define BLUE    3


//to check function is dead or alive
typedef int TaskProfiler;


SemaphoreHandle_t xCountingSemaphore;


void setup() {
  // put your setup code here, to run once:

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // maxCount = , means the number of tasks which can use this semaphore at particular instance.
  xCountingSemaphore = xSemaphoreCreateCounting(1, 0);

  // Create the task 
  xTaskCreate(RedLEDController, "RED LED", 100, NULL, 1, NULL);
  xTaskCreate(GreenLEDController, "GREEN LED", 100, NULL, 1, NULL);
  xTaskCreate(BlueLEDController, "BLUE LED", 100, NULL, 1, NULL);

  xSemaphoreGive(xCountingSemaphore); 

}

TickType_t milliseconds_To_Ticks = pdMS_TO_TICKS(1000);

void RedLEDController(void *pvParameters){


  while(1){
  
    xSemaphoreTake(xCountingSemaphore, 0);
    digitalWrite(RED, digitalRead(RED)^0x1);
    vTaskDelay(milliseconds_To_Ticks);
    xSemaphoreGive(xCountingSemaphore); 

  }
} 



void GreenLEDController(void *pvParameters){


  while(1){


    xSemaphoreTake(xCountingSemaphore, 0);
    digitalWrite(GREEN, digitalRead(GREEN)^0x1);
    xSemaphoreGive(xCountingSemaphore); 
    vTaskDelay(milliseconds_To_Ticks+milliseconds_To_Ticks);
    
  }
} 



void BlueLEDController(void *pvParameters){


  while(1){

    xSemaphoreTake(xCountingSemaphore, 0);
    digitalWrite(BLUE, digitalRead(BLUE)^0x1);
    xSemaphoreGive(xCountingSemaphore); 
    vTaskDelay(milliseconds_To_Ticks+milliseconds_To_Ticks+milliseconds_To_Ticks);

  }
} 




































void loop() {
  // put your main code here, to run repeatedly:

}
