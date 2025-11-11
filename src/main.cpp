#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;
#define SDA 1
#define SCL 2

void sensor_init(VL53L1X::DistanceMode range_mode, bool high_speed) {
  Wire.setPins(SDA,SCL);
  Wire.begin();
  sensor.setTimeout(500);
  sensor.init();
  // sensor.setDistanceMode(range_mode);  
  // int budget = high_speed ? 33000 : 140000;
  // sensor.setMeasurementTimingBudget(budget);
}

void setup() {
  Serial.begin(115200);
  Serial.print("hello world");
  //range_mode: VL53L1X::Short, VL53L1X::Medium, or VL53L1X::Long
  sensor_init(VL53L1X::Long, true);   
}

void loop() {
  //Serial.print("loop\n");
  int dist = sensor.readRangeSingleMillimeters();
  Serial.printf("cm: %i.%i", dist/10, dist%10);
  Serial.print("\tstatus: ");
  Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
  Serial.print("\tpeak signal: ");
  Serial.print(sensor.ranging_data.peak_signal_count_rate_MCPS);
  Serial.print("\tambient: ");
  Serial.print(sensor.ranging_data.ambient_count_rate_MCPS);
  Serial.println();
  delay(500);
}