



// MAIN HIGHLIGHT IS SUSPENDING THE TASK


#include <Arduino_FreeRTOS.h>

#define RED   8
#define GREEN 6
#define BLUE  3

typedef int TaskProfiler;

TaskProfiler REDTaskProfiler;
TaskProfiler GreenTaskProfiler;
TaskProfiler BlueTaskProfiler;


TaskHandle_t RedHandle, GreenHandle, BlueHandle;

uint32_t suspend_monitor;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  xTaskCreate(RedLEDcontroller,"RED Controller", 100, NULL, 1, &RedHandle);
  xTaskCreate(GreenLEDcontroller,"Green Controller", 100, NULL, 1, &GreenHandle);
  xTaskCreate(BlueLEDcontroller,"Blue Controller", 100, NULL, 1, &BlueHandle);

}


void RedLEDcontroller(void *pvParameters){


  pinMode(RED, OUTPUT);
  while(1){

    //REDTaskPriority = uxTaskPriorityGet(RedHandle);
    //Serial.print("RED Task Priority :");
    //Serial.println(REDTaskPriority);
    
    digitalWrite(RED, digitalRead(RED)^1);

  }

}


void GreenLEDcontroller(void *pvParameters){


  pinMode(GREEN, OUTPUT);
  while(1){

    GreenTaskProfiler++;
    //Serial.print("GREEN LED :");
    //Serial.println(GreenTaskProfiler);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    if(suspend_monitor>90000){
      vTaskSuspend(BlueHandle);
    }

  }

}

void BlueLEDcontroller(void *pvParameters){


  pinMode(BLUE, OUTPUT);
  while(1){

    BlueTaskProfiler++;
    //Serial.print("BLUE LED :");
    //Serial.println(BlueTaskProfiler);
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    suspend_monitor++;

  }

}





void loop() {
  // put your main code here, to run repeatedly:

}
