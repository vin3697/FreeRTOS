





#include <Arduino_FreeRTOS.h>
#include "semphr.h"



#define RED    8
#define GREEN  6
#define BLUE   3

//creation of handle - for the interactoin purpose with particular handle of anything (Task/Queue/Timers/Semaphore/Mutex) 

SemaphoreHandle_t xMutex;
TickType_t delayTicks =  pdMS_TO_TICKS(1000);



void setup() {
  // put your setup code here, to run once:

  pinMode(RED  ,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE ,OUTPUT);
  //Creation of Mutex!
  xMutex = xSemaphoreCreateMutex();

  char *RedPtr = "red";
  char *GreenPtr = "green";
  xTaskCreate(LEDTask, "RED LED", 100, RedPtr , 1, NULL);
  xTaskCreate(LEDTask, "GREEN LED", 100, GreenPtr, 1, NULL);
  xTaskCreate(blueLEDTask, "BLUE LED", 100, NULL, 1, NULL);


}

void LEDTask( void *pvParameters){

  while(1){

    if(pvParameters == "red"){
    digitalWrite(RED, digitalRead(RED)^0x1);
    vTaskDelay(delayTicks);
    xSemaphoreTake(xMutex,0);
    }
    else{
    digitalWrite(GREEN, digitalRead(GREEN)^0x1);
    vTaskDelay(delayTicks);
    xSemaphoreGive(xMutex);
    }

  }

}

void blueLEDTask(void *pvParameters){

  while(1){
    xSemaphoreTake(xMutex,0);
    vTaskDelay(delayTicks);
    digitalWrite(BLUE, digitalRead(BLUE)^0x1);
    vTaskDelay(delayTicks);
    xSemaphoreGive(xMutex);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

}
