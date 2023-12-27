

#include <Arduino_FreeRTOS.h>
#include <timers.h>
#define RED   8
#define GREEN 6



#define ONE_SHOT_TIMER     (pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIMER  (pdMS_TO_TICKS(500))


TimerHandle_t oneshotTimer, autoreloadTimer;

BaseType_t oneshotTimerStarted, autoreloadTimerStarted;



void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  oneshotTimer = xTimerCreate(
                                "OneShot",
                                ONE_SHOT_TIMER,
                                pdFAIL,
                                0,
                                t_oneShotTimer
                             );


  autoreloadTimer = xTimerCreate(
                                "AutoREload",
                                AUTO_RELOAD_TIMER,
                                pdPASS,
                                0,
                                t_AutoReloadTimer
                                );


  if((oneshotTimer != NULL)&&(autoreloadTimer != NULL)){
    oneshotTimerStarted    = xTimerStart(oneshotTimer, 0);
    autoreloadTimerStarted = xTimerStart(autoreloadTimer, 0);
  } 

  
  while(((oneshotTimerStarted == pdFAIL) && (autoreloadTimerStarted ==pdFAIL))){

  }
  

}


void t_oneShotTimer(TimerHandle_t xTimer){

  TickType_t xCurrentTime;
  xCurrentTime = xTaskGetTickCount();
  digitalWrite(RED, HIGH);
}

void t_AutoReloadTimer(TimerHandle_t xTimer){
  
  TickType_t xCurrentTime;
  xCurrentTime = xTaskGetTickCount();
  digitalWrite(GREEN, digitalRead(GREEN)^(0x1));

}




void loop() {
  // put your main code here, to run repeatedly:

}
