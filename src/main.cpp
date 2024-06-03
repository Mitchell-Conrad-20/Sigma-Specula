#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "defines.h"
#include "gfx_functions.h"
#include "apps.h"
#include "font.h"
#include "mirror_text.h"




 
void setup() {
  Serial.begin(9600);
  init_gfx();
  display.fillScreen(0);
}

void loop() {
  print_mirrored("TESTING 12345",14,100,16);
}
