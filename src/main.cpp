#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

#define LED 2 // led
#define BACKLIGHT 32 //backlight cpio
#define X_RES 240 // y (rotated)
#define Y_RES 320 // x (rotated)
#define VERTICAL_OFFSET 35
#define DRAW_BUF_SIZE (X_RES * Y_RES / 10 * (LV_COLOR_DEPTH / 8)) // refresh display buffer
TFT_eSPI tft = TFT_eSPI(); // Create TFT object
void* draw_buf;



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


// DEBUG IN PRINTF STYLE TERMINAL ON THE ESP32
template <typename... Args>
void debug(lv_obj_t* debug_obj, const char* format, Args... args){

  char buffer[150];
  sprintf(buffer, format, args...);
  lv_label_set_text_fmt(debug_obj,"%s\n> %s",lv_label_get_text(debug_obj), buffer);


}

lv_obj_t* debug_make(){
  lv_obj_t* out = lv_label_create(lv_scr_act());
  lv_obj_set_size(out, Y_RES,X_RES);
  lv_obj_align(out, LV_ALIGN_TOP_LEFT, 5,VERTICAL_OFFSET-15);
  return out;
}


/*
pio run; git-all; pio run --target upload && pio device monitor -b 115200
*/

void setup() {
  Serial.begin(115200); //listen on port 115200
  //tft.init();
  //tft.setRotation(1);  // Set display rotation (optional)

  // Change background to black
  //tft.fillScreen(TFT_BLACK);
  //// Print some text
  //tft.setTextColor(TFT_RED);  // Set text color to black
  //tft.setTextSize(2);  // Set text size

  //tft.println("HELLO WORLD");
  pinMode(BACKLIGHT, OUTPUT);
  analogWrite(BACKLIGHT, 255);
  //tft.fillRect(0,35, 320,170, TFT_BLACK); // offset in y direction is 35 px
  
  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL);
<<<<<<< HEAD
  //xTaskCreate(print_test, "debug test", 4000, NULL, 1, NULL);
=======
>>>>>>> parent of 3006d6b (nothing of note)
  
  lv_init();
  // malloc_cap_internal : internal flash sotrage
  draw_buf = heap_caps_malloc(DRAW_BUF_SIZE, MALLOC_CAP_DMA); // heap caps malloc: malloc but you can specify where the heap goes
  lv_display_t * disp = lv_tft_espi_create(X_RES, Y_RES, draw_buf, DRAW_BUF_SIZE);
  lv_disp_set_rotation(disp,LV_DISPLAY_ROTATION_90);

  //lv_obj_t *hello = lv_label_create(lv_scr_act());
  //lv_label_set_text(hello, "HELLO\n THERE");
  //lv_obj_align(hello, LV_ALIGN_CENTER,0,0);
  //lv_label_set_text(hello, "h");


  lv_obj_t *d = debug_make();

  char* test = "fdjshckd";
  debug(d,"those who know..%d\t%s",345,test);
  debug(d,"hello worldd%d", 453);

  //tft.setCursor(x_set, y_set);  // Set cursor position
}


void loop() {
  lv_timer_handler();
  delay(5);
  // if (y_set> 195){
  //   i++;
  //   x_set +=170;
  //   y_set = 35;
  // }
  // tft.printf("i use arch btw\n");
  // tft.setCursor(x_set, y_set);
  // //x_set += 10;
  // y_set+= 15;
  // if (i>2){
  //   tft.fillScreen(TFT_BLACK);
  //   x_set = 5;
  //   y_set=35;
  //   i=1;
  //   tft.setCursor(x_set, y_set);
  // }
  // delay(1200);
  //lv_timer_handler();
  // You can add more functionality here
}