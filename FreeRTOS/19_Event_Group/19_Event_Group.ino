





#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define   RED      8
#define   YELLOW   6
#define   BLUE     3



/*
COMMUNICATION + SYNCHRONIZATION of Tasks!
Controlling and Managing Multiple events with the help of bits in the variable!
So these events will be helpful for triggering of the Tasks depending upon the conditions

*/



/*below are the variable, where the bits of it are used to indicate an event wether is has occurred or not
and this toggling of bit will help us to trigger a particular Task
*/
#define TASK1_BIT   (1UL << 0UL)  // 0th bit of variable set to 1
#define TASK2_BIT   (1UL << 1UL)  // 1st bit of variable set to 1
#define TASK3_BIT   (1UL << 2UL)  // 2nd bit of variable set to 1

EventGroupHandle_t  xEventGroup;

const TickType_t xDelay500ms =  pdMS_TO_TICKS(500);
void setup()
{


  // creation of Event Group
   xEventGroup  =  xEventGroupCreate();

   xTaskCreate(InputTask1, "Input Task 1", 100,NULL,1,NULL);
   xTaskCreate(InputTask2, "Input Task 2", 100, NULL, 1, NULL );
   xTaskCreate(InputTask3, "Input Task 3", 100, NULL, 1,NULL);
   xTaskCreate(OutputTask, "Output Task", 100, NULL, 1, NULL);
   
}

void InputTask1(void *pvParameters)
{
  while(1)
  {

    //setting the bit for particular task when the task is executed!!!!
     xEventGroupSetBits(xEventGroup, TASK1_BIT);
     vTaskDelay(xDelay500ms);


  }
}
void InputTask2(void *pvParameters)
{
  while(1)
  {
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    vTaskDelay(xDelay500ms);
  }
}


void InputTask3(void *pvParameters)
{
  while(1)
  {
    xEventGroupSetBits(xEventGroup,TASK3_BIT);
    vTaskDelay(xDelay500ms);
  }
}


void OutputTask(void *pvParameters)
{ 
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  
  const EventBits_t xBitsToWaitFor  = (TASK1_BIT | TASK2_BIT | TASK3_BIT);
  EventBits_t xEventGroupValue;
  while(1)
  {
    xEventGroupValue  = xEventGroupWaitBits(xEventGroup,
                                            xBitsToWaitFor,
                                            pdTRUE,
                                            pdTRUE,
                                            portMAX_DELAY
                                            );
   if((xEventGroupValue & TASK1_BIT) !=0)
   {
    digitalWrite(RED,digitalRead(RED)^1);
   }
   if((xEventGroupValue & TASK2_BIT !=0))
   {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
   }
   if((xEventGroupValue & TASK3_BIT !=0))
   {
    digitalWrite(BLUE,digitalRead(BLUE)^1);
   }
  }
}
void loop(){}
