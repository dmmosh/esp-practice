#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>

#include <TFT_eSPI.h>
#include "BluetoothSerial.h"

#define LED 2 // led
#define BACKLIGHT 32 //backlight cpio
#define X_RES 240 // y (rotated)
#define Y_RES 320 // x (rotated)
#define VERTICAL_OFFSET 35
#define DRAW_BUF_SIZE (X_RES * Y_RES / 10 * (LV_COLOR_DEPTH / 8)) // refresh display buffer
TFT_eSPI tft = TFT_eSPI(); // Create TFT object
BluetoothSerial SerialBT;
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
    //Serial.printf("%i\n", i);
  }
}


unsigned int x_set = 5; 
unsigned int y_set = 35; 
unsigned int i = 1;
template<typename ...Args>
void debug(const char* format, Args... args){

  if (y_set> 190){ // to go col 2 
    i++;
    x_set +=170;
    y_set = 35;
  }

  if (i>2){ // reset
    tft.fillScreen(TFT_BLACK);
    x_set = 5;
    y_set=35;
    i=1;
    //tft.setCursor(x_set, y_set);
  }

  tft.setCursor(x_set, y_set);

  tft.printf(format, args...);

  y_set+= 20;
  //x_set += 10;
}

void vTaskMemoryUsage(void *pvParameters)
{
    while(1){
    // Get the task handle
    TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();
    
    // Get the high-water mark of the task's stack (bytes left)
    UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(xTaskHandle);
    
    // Optionally, print the stack size (this is the total stack size)
    UBaseType_t uxTaskStackSize = configMINIMAL_STACK_SIZE; // Or your stack size
    
    debug("mem: %i | %i", uxHighWaterMark, uxTaskStackSize);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }


}

/*
pio run; git-all; pio run --target upload && pio device monitor -b 115200
*/

void setup() {
  Serial.begin(115200); //listen on port 115200

  SerialBT.begin("ESP32test");

  // tft gui basic 
  tft.init();
  tft.setRotation(1);  // Set display rotation (optional)

  tft.fillScreen(TFT_BLACK);
  // Print some text
  tft.setTextColor(TFT_RED);  // Set text color to black
  tft.setTextSize(2);  // Set text size
  //tft.fillRect(0,35, 320,170, TFT_BLACK); // offset in y direction is 35 px

  tft.setCursor(x_set, y_set);  // Set cursor position

  pinMode(BACKLIGHT, OUTPUT);
  analogWrite(BACKLIGHT, 255);
  
  xTaskCreate(led, "blink led", 1048, NULL, 1, NULL);
  //xTaskCreate(vTaskMemoryUsage, "task monitor", 2048, NULL, 1, NULL);
  //xTaskCreate(print_test, "debug test", 4000, NULL, 1, NULL);
  
 

}


char buffer[101];
uint8_t chr = 0;
void loop() {

  // // check for message from serial monitor
  // if (Serial.available()){
  //   SerialBT.write(Serial.read());
  // }

  // //check for message from a paired bluetooth
  // if (SerialBT.available()){
  //   Serial.write(SerialBT.read());
  // }

  if (SerialBT.available()){

    char curr = SerialBT.read();

    switch(curr){
      case '\n':
        buffer[chr] = '\0';
        debug("%s",buffer);
        chr=0;
      break;
      default:
        buffer[chr] = curr;
        chr++;
    }
    if(chr>99) chr = 0;
  }
  delay(5);
  //lv_timer_handler();
}


//LVGL CODE 
/*
#include <lvgl.h>

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
  //debug(d,"those who know..%d\t%s",345,test);
  //debug(d,"hello worldd%d", 453);

*/