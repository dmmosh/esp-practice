#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#define LED 2 // led
#define BACKLIGHT 32 //backlight cpio
#define X_RES 100
#define Y_RED 100


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


TFT_eSPI tft = TFT_eSPI(); // Create TFT object

static uint32_t my_tick(void)
{
    return millis();
}

void setup() {
  Serial.begin(9600); //listen on port 9600
  tft.init(); // init serial connection
  analogWrite(BACKLIGHT, 255); // make brightness max
  pinMode(BACKLIGHT, OUTPUT); // set brightness
  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL); //blinking led task
  //tft.setRotation(1);  // Set display rotation (optional)
  lv_init();
  lv_tick_set_cb(my_tick);

  lv_display_t* disp = lv_display_create(X_RES, Y_RED);
  lv_display_set_rotation(disp, LV_DISP_ROTATION_90);
  lv_obj_t *label = lv_label_create( lv_screen_active() );
    lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

    Serial.println( "Setup done" );
  

}

void loop() {
  lv_timer_handler();
  delay(5);
  // You can add more functionality here
}