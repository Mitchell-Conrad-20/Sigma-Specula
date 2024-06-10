
#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "esp32notifications.h"
#include <BLEDevice.h>
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
  
  // init_gfx();
  // display->fillScreen(0);
  // deinit_display();
  // init_ancs();
}
void loop() {
  delay(200);
   
  // Define the GPIO pin for the button
  const int buttonPin = 0;

  // Configure the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Read the state of the button
  int buttonState = digitalRead(buttonPin);
  
  // Check if the button is pressed
  if (buttonState == LOW) {
    // The button is pressed
    //Serial.println("Button is pressed!");
    draw_debug();
  } 
 
}
