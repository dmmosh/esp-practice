#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

#define LED 2 // led
#define BACKLIGHT 32 //backlight cpio
#define X_RES TFT_WIDTH
#define Y_RES TFT_HEIGHT
#define CURR lv_scr_act() //current active screen 
#define DRAW_BUF_SIZE (X_RES * Y_RES / 10 * (LV_COLOR_DEPTH / 8))
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




/*
pio run; git-all; pio run --target upload && pio device monitor -b 115200
*/

unsigned int x_set = 5; 
unsigned int y_set = 35; 
unsigned int i = 1;

void setup() {
  Serial.begin(115200); //listen on port 9600
  tft.init();
  tft.setRotation(1);  // Set display rotation (optional)

  // Change background to black
  tft.fillScreen(TFT_WHITE);
  
  // Print some text
  tft.setTextColor(TFT_BLACK);  // Set text color to black
  tft.setTextSize(2);  // Set text size

  //tft.println("HELLO WORLD");
  pinMode(BACKLIGHT, OUTPUT);
  analogWrite(BACKLIGHT, 250);
  //tft.fillRect(0,35, 320,170, TFT_BLACK); // offset in y direction is 35 px
  
  xTaskCreate(led, "blink led", 2048, NULL, 1, NULL);
  //tft.setRotation(1);  // Set display rotation (optional)
  // lv_init();
  // //lv_tick_set_cb(my_tick);

  // draw_buf = heap_caps_malloc(DRAW_BUF_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
  // lv_display_t * disp = lv_tft_espi_create(X_RES, Y_RES, draw_buf, DRAW_BUF_SIZE);


  // lv_obj_t *label = lv_label_create( CURR );
  // lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
  // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

  // Serial.println( "Setup done" );


  tft.setCursor(x_set, y_set);  // Set cursor position
}


void loop() {
  if (x_set > 320){
    i++;
    x_set = 5*i;
  }
  if (5*i > 320){
    i = 2;
  }

  if (y_set> 205){
    x_set +=10;
    y_set = 35;
  }
  tft.printf("i use arch btw\n");
  tft.setCursor(x_set, y_set);
  //x_set += 10;
  y_set+= 10;
  delay(2000);
  //lv_timer_handler();
  // You can add more functionality here
}