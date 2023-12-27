








#include <Arduino_FreeRTOS.h>
#include "timers.h"



#define RED    8
#define GREEN  6


#define AR_timerOnePeriod (pdMS_TO_TICKS(100))
#define AR_timerTwoPeriod (pdMS_TO_TICKS(200))

// AR - autoreload timer
TimerHandle_t AR_timerOne;
TimerHandle_t AR_timerTwo; 

BaseType_t AR_timerOneStarted, AR_timerTwoStarted;


void setup() {
  // put your setup code here, to run once:

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  //Create the Timer refering to Handle
  AR_timerOne = xTimerCreate("AR_timerOne", AR_timerOnePeriod, pdPASS,0, AR_timerCAllBackFunction);
  AR_timerTwo = xTimerCreate("AR_timerTwo", AR_timerTwoPeriod, pdPASS,0, AR_timerCAllBackFunction);


  if((AR_timerOne != NULL) && (AR_timerTwo != NULL)){

    AR_timerOneStarted = xTimerStart(AR_timerOne,0);
    AR_timerTwoStarted = xTimerStart(AR_timerTwo,0);
  }

}


uint32_t redLEDcount, greenLEDcount;
void AR_timerCAllBackFunction(TimerHandle_t xTimer){

  if(xTimer == AR_timerOne){
    digitalWrite(RED, digitalRead(RED)^0x1);
    redLEDcount++;
    if(redLEDcount == 50){
      xTimerStop(AR_timerOne,0);
      redLEDcount = 0;
    }
  }
  else{
    digitalWrite(GREEN, digitalRead(GREEN)^0x1);
    greenLEDcount++;
    if(greenLEDcount == 100){
      xTimerStart(AR_timerOne, 0);
      greenLEDcount = 0;
    }
  }


}

void loop() {  // put your main code here, to run repeatedly:
}































