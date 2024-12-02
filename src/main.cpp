#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#define LED 2 // led

void led(void* args){
  int i = 1000;
  while(1){
    digitalWrite(LED, HIGH);
    vTaskDelay(i/portTICK_PERIOD_MS);
    digitalWrite(LED, LOW);
    vTaskDelay(i/portTICK_PERIOD_MS);
    i= (int)((float)i /1.2);
    if(i == 0){
      i = 1000;
    }
    Serial.printf("%i\n", i);
  }
}

/*
RUN AND COMPILE (with git-all)
pio run; git-all; pio run --target upload && pio device monitor


*/

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);

  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL);

}

void loop() {}
