#include <Arduino.h>

#define CONTROL 15

void setup() {
  pinMode(CONTROL, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  digitalWrite(CONTROL,HIGH);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  digitalWrite(CONTROL,LOW);
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
