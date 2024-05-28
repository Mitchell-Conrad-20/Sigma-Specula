#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "defines.h"

bool init_gfx(){
  // Initial setup of graphics library
  display.begin();
  return true;
}

void display_clear(){
  display.waitForFrame();
  display.fillScreen(0);
}
 
void setup() {
  init_gfx();
}

void loop() {
  // clear display
  display_clear();
  // redraw material 
  display.drawRoundRect(25,25,50,50,4,CYAN);
  display.setTextSize(1); // Set text size to 1 (smallest)
  display.setTextColor(RED);
  display.setCursor(0, 0);
  display.println(word_vomit);
}

 