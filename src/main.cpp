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

/*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   100
#define TFT_VER_RES   100
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

TFT_eSPI tft = TFT_eSPI();  // Create TFT object


/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

#if LV_USE_LOG != 0
void my_print( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{

    uint16_t width = area->x2 - area->x1 + 1;
    uint16_t height = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, area->x2, area->y2);
    tft.pushColor((uint16_t)px_map, width * height);
    tft.endWrite();

    /*Call it to tell LVGL you are ready*/
    lv_display_flush_ready(disp);
}



/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
    return millis();
}

void setup()
{
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.begin( 115200 );
    Serial.println( LVGL_Arduino );

    lv_init();

    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);

    /* register print function for debugging */
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print );
#endif

    lv_display_t * disp;
#if LV_USE_TFT_ESPI
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

#else
    /*Else create a display yourself*/
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif


     


    lv_obj_t *label = lv_label_create( lv_screen_active() );
    lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5); /* let this time pass */
}

