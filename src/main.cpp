#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// #define LED 2 // led
// #define X_RES   100
// #define Y_RES   100
// #define TFT_ROTATION  LV_DISPLAY_ROTATION_0

// void led(void* args){
//   int i = 1000;
//   while(1){
//     digitalWrite(LED, HIGH);
//     vTaskDelay(i/portTICK_PERIOD_MS);
//     digitalWrite(LED, LOW);
//     vTaskDelay(i/portTICK_PERIOD_MS);
//     i= (int)((float)i /1.2);
//     if(i == 0){
//       i = 1000;
//     }
//     Serial.printf("%i\n", i);
//   }
// }

// /*
// RUN AND COMPILE (with git-all)
// pio run; git-all; pio run --target upload && pio device monitor


// */

// static uint32_t my_tick(void)
// {
//     return millis();
// }

// void setup() {
//   Serial.begin(9600);
//   // put your setup code here, to run once:
//   pinMode(LED, OUTPUT);
//   lv_init();
//   lv_tick_set_cb(my_tick);

//   lv_obj_t *label = lv_label_create( lv_screen_active() );
//   lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
//   lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );


//   xTaskCreate(led, "blink led", 2048, NULL, 1, NULL);

// }

// void loop() {}

/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */

#include <lvgl.h>

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 *as the examples and demos are now part of the main LVGL library. */

//#include <examples/lv_examples.h>
//#include <demos/lv_demos.h>

#include <Arduino.h>
#include <TFT_eSPI.h> 
TFT_eSPI tft = TFT_eSPI();

void setup() 
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0,0,4);
  tft.setTextColor(TFT_WHITE);
  tft.println ("Hello World!");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
