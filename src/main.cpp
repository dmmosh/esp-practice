#include <Arduino.h>
/*
 * LAB Name: ESP32 DAC Direct Voltage Output Example
 * Author: Khaled Magdy
 * DeepBlueMbedded 2023
 * For More Info Visit: www.DeepBlueMbedded.com
*/
 
#define DAC_CH1 25
 
void setup() 
{
  // DO NOTHING
}
 
void loop() 
{
  // Send Output DC Voltage Raw Values To The DAC
  // (0  64  128 192 255)
  // Insert Delay After Each Sample Output
  for(int i =0; i<256; i++){
      dacWrite(DAC_CH1, i);
      delay(10);
  }
}