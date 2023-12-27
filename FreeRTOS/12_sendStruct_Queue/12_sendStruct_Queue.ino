


#include <Arduino_FreeRTOS.h>
#include <queue.h>


typedef enum{
  TxSender_One,
  TxSender_Two
}TxSender;

typedef struct{
  uint32_t qValue;
  TxSender qTxSender;
}qSender;


typedef int TaskProfiler;
TaskProfiler Sender_One;
TaskProfiler Sender_Two;
TaskProfiler Receiver;

QueueHandle_t _qData;


void setup(){


  Serial.begin(9600);
  _qData = xQueueCreate(5, sizeof(qSender));
  qSender DataTx_Q[2] = {{100,TxSender_One},
                        {800, TxSender_Two }};
  xTaskCreate(TX_Controller, "TX Q Data Sender One", 100, &(DataTx_Q[0]), 1, NULL);
  xTaskCreate(TX_Controller, "TX Q Data Sender Two", 100, &(DataTx_Q[1]), 1, NULL); 
  /* 
  Structure Data has been passed with help of Address!!!
  
  */

  //xTaskCreate(RX_Controller, "RX Data", 100, NULL, 1, NULL)

}

const TickType_t _msToTick = pdMS_TO_TICKS(100); 

void TX_Controller(void *pvParameters){
  
  BaseType_t qStatus;
  // Cast the void pointer to the appropriate data type (qSender*)
  qSender DATASEND = *((qSender *)pvParameters);   

  while(1)
  {
    Serial.print("Sender : ");
    Serial.println(uint32_t(DATASEND.qValue));
    //qStatus = xQueueSend(_qData, DATASEND, _msToTick);

  }  

}
/**
*@param ARROW_OPERATOR
*@code{start}

void TX_Controller(void *pvParameters) {
  BaseType_t qStatus;  

  // Cast the void pointer to the appropriate data type (qSender*)
  qSender *data = (qSender*)pvParameters;

  while(1) {
    qStatus = xQueueSend(_qData, data, _msToTick);
    if(qStatus == pdPASS) {
      Serial.print("Sender: ");
      Serial.print(data->qValue); // Accessing the qValue member
      Serial.print(" from Sender ");
      if (data->qTxSender == TxSender_One) {
        Serial.println("One");
      } else if (data->qTxSender == TxSender_Two) {
        Serial.println("Two");
      }
    }
  }  
}
*@code{end}


*/

/**
* @param DOT_OPERATOR

*@code{start}

void TX_Controller(void *pvParameters) {
  BaseType_t qStatus;  

  // Cast the void pointer to the appropriate data type (qSender*)
  qSender *data = (qSender*)pvParameters;

  while(1) {
    qStatus = xQueueSend(_qData, data, _msToTick);
    if(qStatus == pdPASS) {
      Serial.print("Sender: ");
      Serial.print((*data).qValue); // Accessing the qValue member using dot operator with explicit dereferencing
      Serial.print(" from Sender ");
      if ((*data).qTxSender == TxSender_One) {
        Serial.println("One");
      } else if ((*data).qTxSender == TxSender_Two) {
        Serial.println("Two");
      }
    }
  }  
}

*/


/**
* @param DOT_OPERATOR 
* 
* @code{start}

void TX_Controller(void *pvParameters) {
  BaseType_t qStatus;  

*@param IMPORTANT -  qSender data = *((qSender*)pvParameters); // Copy the structure from the void pointer

  while(1) {
    qStatus = xQueueSend(_qData, &data, _msToTick); // Pass the address of the structure
    if(qStatus == pdPASS) {
      Serial.print("Sender: ");
      Serial.print(data.qValue); // Accessing the qValue member using the dot operator
      Serial.print(" from Sender ");
      if (data.qTxSender == TxSender_One) {
        Serial.println("One");
      } else if (data.qTxSender == TxSender_Two) {
        Serial.println("Two");
      }
    }
  }  
}


 */






void loop(){

}