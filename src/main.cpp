#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

#define LED 2 // led
#define BACKLIGHT 32 //backlight cpio
#define X_RES 100
#define Y_RES 100
#define CURR lv_screen_active() //current active screen 

#define DRAW_BUF_SIZE (X_RES * Y_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];


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


void setup() {
  Serial.begin(9600); //listen on port 9600
  tft.init(); // init serial connection
  analogWrite(BACKLIGHT, 255); // make brightness max
  pinMode(BACKLIGHT, OUTPUT); // set brightness
  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL); //blinking led task
  //tft.setRotation(1);  // Set display rotation (optional)
  lv_init();
  //lv_tick_set_cb(my_tick);

  lv_display_t* disp = lv_tft_espi_create(X_RES, Y_RES, draw_buf, sizeof(draw_buf));
  //lv_display_set_rotation(disp, LV_DISP_ROTATION_90);


  lv_obj_t *label = lv_label_create( CURR );
  lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
  lv_obj_set_style_bg_color(CURR, LV_COLOR_MAKE(100,100,100),0);

  lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
  Serial.println( "Setup done" );
  

}

void loop() {
  lv_timer_handler();
  delay(5);
  // You can add more functionality here
}