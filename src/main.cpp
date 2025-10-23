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
  dacWrite(DAC_CH1, 0);
  delay(100);
  dacWrite(DAC_CH1, 64);
  delay(100);
  dacWrite(DAC_CH1, 128);
  delay(100);
  dacWrite(DAC_CH1, 192);
  delay(100);
  dacWrite(DAC_CH1, 255);
  delay(100);
}