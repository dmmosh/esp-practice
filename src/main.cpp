#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#define LED 2 // led
#define X_RES   100
#define Y_RES   100
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

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

static uint32_t my_tick(void)
{
    return millis();
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  lv_init();
  lv_tick_set_cb(my_tick);

  lv_obj_t *label = lv_label_create( lv_screen_active() );
  lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
  lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );


  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL);

}

void loop() {}
