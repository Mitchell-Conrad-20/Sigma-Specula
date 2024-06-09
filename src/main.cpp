
#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "defines.h"
#include "gfx_functions.h"
#include "apps.h"
#include "font.h"
#include "mirror_text.h"
#include "ancs_notifications.h"


void setup() {
  Serial.begin(9600);
  while(!Serial) {
        delay(10);
  }
  init_ancs();
  delay(3000);
  stop_ancs();
  init_gfx();
  display->fillScreen(0);
  // deinit_display();
  // init_ancs();
}

void loop() {
  delay(200);
  display_clear();
  print_mirrored("TESTING 12345",14,100,16, MAGENTA);
  print_mirrored("TESTING 12345",14,140,8, WHITE);
}
