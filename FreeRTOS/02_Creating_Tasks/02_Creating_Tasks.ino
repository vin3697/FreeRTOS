#include <Arduino_FreeRTOS.h>
#define RED   8
#define GREEN 6
#define BLUE  3 

typedef int TaskProfiler; // profiler are useful to check whether the thread/task is dead or alive!

TaskProfiler RedLEDProfiler;
TaskProfiler GreenLEDProfiler;
TaskProfiler BlueLEDProfiler;

void setup(){
  Serial.begin(9600);


  //create the tasks
  xTaskCreate(redLEDControllerTask,
              "RED LED Task",
              100, //stack
              NULL,//arguments to the task
              1,   //Priority
              NULL

  );

  xTaskCreate(GreenLEDControllerTask,
              "GREEN LED Task",
              100,
              NULL,
              3,
              NULL

  );

  xTaskCreate(BlueLEDControllerTask,
              "BLUE LED Task",
              100, 
              NULL,
              2,
              NULL

  );
}


void redLEDControllerTask(void *pvParameters){
  
  pinMode(RED, OUTPUT);

  while(1){
    digitalWrite(RED, digitalRead(RED)^1);
    //delay(1000);
  }

}


void GreenLEDControllerTask(void *pvParameters){
  
  pinMode(GREEN, OUTPUT);

  while(1){
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    //delay(1000);
  }

}


void BlueLEDControllerTask(void *pvParameters){
  
  pinMode(BLUE, OUTPUT);

  while(1){
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    //delay(1000);
  }

}

void loop(){
  
}