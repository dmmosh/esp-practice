#include "header.h"

extern "C"{
    void app_main(void);
}

void app_main(void)
{
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    blink();    
}