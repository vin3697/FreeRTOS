



#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED    8
#define GREEN  6

QueueHandle_t TxQueue_One;
QueueHandle_t TxQueue_Two;

QueueSetHandle_t xQueueSet;

void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);
  TxQueue_One = xQueueCreate(1, sizeof(char *));
  TxQueue_Two = xQueueCreate(1, sizeof(char *));


  /**
    @code Queue Set

  */
  xQueueSet = xQueueCreateSet(1*2);
  xQueueAddToSet(TxQueue_One,xQueueSet);
  xQueueAddToSet(TxQueue_Two,xQueueSet);

  xTaskCreate(SenderTaskOne, "Sender One", 100, NULL, 1, NULL);
  xTaskCreate(SenderTaskTwo, "Sender Two", 100, NULL, 1, NULL);
  xTaskCreate(ReceiverTaskOne, "Receiver ", 100, NULL, 1, NULL);

}



void SenderTaskOne(void *pvParameters){

  pinMode(RED, OUTPUT);
  const TickType_t _msToTicksBlockTime = pdMS_TO_TICKS(100);
  const char *const msg = "SEDNER ONE";

  while(1){
    xQueueSend(TxQueue_One, &msg, 0);
    digitalWrite(RED, digitalRead(RED)^1);
    vTaskDelay(_msToTicksBlockTime);
  }

}

void SenderTaskTwo(void *pvParameters){

  pinMode(GREEN, OUTPUT);
  const TickType_t _msToTicksBlockTime = pdMS_TO_TICKS(200);
  const char *const msg = "SEDNER TWO";

  while(1){
    xQueueSend(TxQueue_Two, &msg, 0);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    vTaskDelay(_msToTicksBlockTime);
  }

}

void ReceiverTaskOne(void *pvParameters){

  QueueHandle_t xQueueContainsData;
  char *RxDatafrombothQ;

  xQueueContainsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
  //BaseType_t RxStatus;
  while(1){
    xQueueReceive(xQueueContainsData, &RxDatafrombothQ, 0);
    Serial.println(RxDatafrombothQ);
  }

}





void loop() {
  // put your main code here, to run repeatedly:

}
