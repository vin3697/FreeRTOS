

#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     8
#define GREEN   6
#define BLUE    3



QueueHandle_t birthYear;


const TickType_t _500msDelay = pdMS_TO_TICKS(500);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  birthYear = xQueueCreate(5, sizeof(uint32_t));

  //Tasks created to send the data to the Queue via TxTask function
  //Passing Argument to the TxTask fucntion as well
  xTaskCreate(TxTask, "Tx Task", 100, (void *)1997, 1, NULL);
  xTaskCreate(TxTask, "Tx Task", 100, (void *)2023, 1, NULL);

  //without adding delay this script wont work, as the RX task has 2nd priority which will always take the processor for granted!!!
  //and we can use normal delay or vTaskDelay(Ticks_TO_ms) delay function, just to make sure the processor gets some free time to process other Tasks!
  xTaskCreate(RxTask, "Rx Task", 100, NULL, 2, NULL);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}


void TxTask(void *pvParameters){


  BaseType_t qTxStatus;

  uint32_t DataToQueue;
  DataToQueue = (uint32_t)pvParameters;

  while(1){

  qTxStatus = xQueueSend(birthYear, &DataToQueue, 0);
  if(qTxStatus){
    digitalWrite(RED, digitalRead(RED)^1);
    //delay(1000);
    vTaskDelay(_500msDelay);
    Serial.print("TX DATA : ");
    Serial.println(DataToQueue);
    }
  }
}



void RxTask(void *pvParameters){

  BaseType_t qRxStatus;
  const uint32_t DatafromQueue;
  const TickType_t _ms_xTickToWait = pdMS_TO_TICKS(100);
  while(1){
    qRxStatus = xQueueReceive(birthYear, &DatafromQueue, _ms_xTickToWait);
    if(qRxStatus){
      Serial.print("RX DATA : ");
      Serial.println(DatafromQueue);
      if(DatafromQueue == 1997){
      digitalWrite(GREEN, digitalRead(GREEN)^1);
      //delay(100);
      vTaskDelay(_500msDelay);

      }
      if(DatafromQueue == 2023){
      digitalWrite(BLUE, digitalRead(BLUE)^1);
      //delay(300);
      vTaskDelay((_500msDelay+_500msDelay));

      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
