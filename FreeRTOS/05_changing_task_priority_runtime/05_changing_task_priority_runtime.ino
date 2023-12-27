



// will be using Task Handle Parameter in the xTaskCreate structure function
// DONT ADD DELAY AND OBSERVE THE OUTPUT
// LED REMAINS "ON" when the "while loop" executes one time and changes the priority of a task to higher and then doesnt executed further!!!!!!!
// The hardware is stuck on the "ON" part of the toggle condition :)

#include <Arduino_FreeRTOS.h>

#define RED   8
#define GREEN 6
#define BLUE  3

typedef int TaskProfiler;
TaskProfiler RedLEDTaskProfiler;
TaskProfiler GreenLEDTaskProfiler;
TaskProfiler BlueLEDTaskProfiler;

TaskHandle_t red_Handle, green_Handle, blue_Handle;

void setup() {
  // put your setup code here, to run once:

  xTaskCreate(redLEDController, "Red LED", 100, NULL, 1 ,&red_Handle);
  xTaskCreate(GreenLEDController, "Green LED", 100, NULL, 1 ,&green_Handle);
  xTaskCreate(BlueLEDController, "Blue LED", 100, NULL, 1 ,&blue_Handle);


}

void redLEDController(void *pvParameters){

  pinMode(RED, OUTPUT);

  while(1){
    digitalWrite(RED, digitalRead(RED)^1);
    //vTaskPrioritySet(blue_Handle, 3);
    //delay(50);
  }
  
}


void GreenLEDController(void *pvParameters){

  pinMode(GREEN, OUTPUT);

  while(1){
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    vTaskPrioritySet(red_Handle, 3);
    //delay(50);
  }
}


void BlueLEDController(void *pvParameters){

  pinMode(BLUE, OUTPUT);

  while(1){
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    vTaskPrioritySet(red_Handle, 3);
    //delay(50);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
