#include <Arduino.h>
#define LED 2
#define DPLUS 13
#define DMINUS 12

void setup(){
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(DPLUS,INPUT_PULLUP);
  pinMode(DMINUS,INPUT_PULLUP);
}

void loop(){
  Serial.printf("%i, %i\n", digitalRead(DPLUS), digitalRead(DMINUS));
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}