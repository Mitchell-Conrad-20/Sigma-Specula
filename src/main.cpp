#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "defines.h"
#include "gfx_functions.h"
#include "apps.h"
#include "QuickCapTouch.h"

QuickCapTouch sensor = QuickCapTouch(27, 30, 1000);
 
void setup() {
  Serial.begin(115200);
  init_gfx();
}

void loop() {
  // clear display
  main_app_screen();
  sensor.tick();
  Serial.println(sensor.getState());
}