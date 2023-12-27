

#include <Arduino_FreeRTOS.h>


#define RED    8
#define GREEN  6
#define BLUE   3

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler GreenLEDProfiler;
TaskProfiler BlueLEDProfiler;

void setup() {
  // put your setup code here, to run once:


  uint16_t *redLEDptr   = (uint16_t *)RED;
  uint16_t *greenLEDptr = (uint16_t *)GREEN;
  uint16_t *blueLEDptr  = (uint16_t *)BLUE;


  //here changing the priority hardly works, but in source code of 02_Creating_Tasks the priority is important!!
  // above statement is wrong!!!, this is caused because of the delay inclusion in the source code.
  //AND THE THREAD OR TASKA ARE NOT SYNCHORNIZED! Round Robin Scheduling is implemented while using the processor

  xTaskCreate(LEDcontrollerTask, "LED controller", 100, (void *)redLEDptr, 1, NULL);
  xTaskCreate(LEDcontrollerTask, "LED controller", 100, (void *)greenLEDptr, 3, NULL);
  xTaskCreate(LEDcontrollerTask, "LED controller", 100, (void *)blueLEDptr, 1, NULL);

}

void LEDcontrollerTask( void *pvparameter){
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  while(1){
    digitalWrite(pvparameter, digitalRead(pvparameter) ^ 1);
    //delay(100);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
