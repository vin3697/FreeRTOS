 
#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 8

QueueHandle_t birthDateMonthYear;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(600);
  birthDateMonthYear = xQueueCreate(5, sizeof(int32_t));
  xTaskCreate(TxQueue, "Send Queue", 100, NULL, 1, NULL);
  xTaskCreate(RxQueue, "Recieve Queue", 100, NULL, 1, NULL);
}

void TxQueue(void *pvParameters){
  
  // typedef int8_t BaseType_t;
  BaseType_t qTxstatus;
  const uint32_t TxValue = 1997;
  while(1){

    qTxstatus = xQueueSend(birthDateMonthYear, (void *)&TxValue, 0);

  }

}


void RxQueue(void *pvParameters){
  
  BaseType_t qRxstatus;
  const uint32_t RxValue;
  //typedef uint16_t TickType_t;
  const TickType_t xTicksToWait_ms = pdMS_TO_TICKS(1000); //100ms

  pinMode(RED, OUTPUT);
  while(1){
    qRxstatus = xQueueReceive(birthDateMonthYear, (void *)&RxValue, xTicksToWait_ms);

    Serial.print("Rx value is : ");
    Serial.println(RxValue);
    
    if(qRxstatus){
      digitalWrite(RED, digitalRead(RED)^1);
      vTaskDelay(xTicksToWait_ms);
    }
  }


}


void loop() {
  // put your main code here, to run repeatedly:

}
