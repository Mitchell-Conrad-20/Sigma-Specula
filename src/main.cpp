#include <Arduino.h>
#include "rtc.h"
#include "esp32notifications.h"
#include <U8g2lib.h>
#include <NimBLEDevice.h>
#include <NimBLEDescriptor.h>
#include <NimBLEAdvertisedDevice.h>
#include <ESP32Time.h>
#include "NotificationList.h"
#include "QuickCapTouch.h"
#include <Wire.h>
#include "defines.h"
#include "image_bitmaps.h"
#include "display_functions.h"
#include "direction.h"
#include "ancs_notifications.h"
#include "applications.h"

 


void setup() {
  Serial.begin(9600);
  u8g2.begin();
  init_ancs();
  delay(500);
  draw_home();
}
int pl= 0; 
void loop() {
  delay(100);
  sensor.tick();
  unsigned long current_time = millis();
  // Simulated sensor tick, replace with actual sensor reading
  int sensorState = sensor.getState();
  touch = 0; 
  if (sensorState == 1 && hold_time == 0) {
    // Sensor active and hold time not started
    hold_time = current_time; // Start counting hold time
  } else if (sensorState == 0 && hold_time > 0) {
    // Sensor inactive and hold time started
    unsigned long elapsed;
    if (current_time >= hold_time) {
      elapsed = current_time - hold_time; // Normal calculation
    } else {
      elapsed = (ULONG_MAX - hold_time) + current_time + 1; // Handle rollover
    }
    if(elapsed < 300){
      touch = 1; // short press
    }else if(elapsed > 300){
      touch = 2; // long press 
    }
    //Serial.println(elapsed); // Output hold time
    hold_time = 0; // Reset hold time
  }
  if(touch > 0){
    if(timeout_counter > 50){
      turn_on_display();
    }else{
      if(touch == 1){
        refresh_flag = true;
        print("Short press...");
        short_press = 1; 
      }
      if(touch == 2){
        refresh_flag = true;
        print("Long press....");
        long_press = 1; 
      }
    }
    timeout_counter = 0; // reset the sleep counter
  }else{
    timeout_counter += 1; // iterate the sleep counter
  }
  if(timeout_counter > 50){
    if(gui_state == 0){ // put the states for which the display will sleep here. (for now just the homescreen)
      turn_off_display();   
    }
    int pl=0;
  }
  
  switch (gui_state) {
    case 0: // home 
      if(long_press || short_press || refresh_flag){ 
        Serial.println("Going to homescreen");
        draw_home();
      }     
      if(refresh_flag){ // write to this flag to force refresh. This resets the flag
         refresh_flag = false;
      }
      break;
    case 1: // app screen
    if(long_press || short_press || refresh_flag){
        if(refresh_flag){ // write to this flag to force refresh. This resets the flag
         refresh_flag = false;
        }
        if(short_press){
          short_press = 0;
          if(app_select <= 1){ // set which bitmap to show (for the app -> 0 is nav and 1 is messages currently)
            app_select++;
          }else{
            app_select = 0; 
          }
        }else if(long_press){
          long_press = 0;
          short_press = 0;
          switch (app_select) {
            case 0:
              print("Navigation selected!");
              app_select = 10;
              gui_state = 40;
              break;
            case 1:
              if(gui_state == 30){
                print("Returning to home screen!");
                gui_state = 0; 
                refresh_flag = true; // refresh the screen!
              }else{
                print(String(gui_state));
                print("Messages selected!");
                gui_state = 30;
                refresh_flag = true;
              }
              
              break;
            case 2:
              print("Returning to home screen!");
              gui_state = 0; 
              refresh_flag = true; // refresh the screen!
              break;
          }
        }
        Serial.println("Going to app selection");
        draw_app(app_select);
        
      } 
      break;
    case 30:
      if(long_press || short_press || refresh_flag){ 
        print("Messages selected!");
        draw_message("Tim","Erm what the sigma?");
      }     
      if(refresh_flag){ // write to this flag to force refresh. This resets the flag
         refresh_flag = false;
      }
      break;
    case 40: // driving / navigation
      if(app_select == 10){
        driving_app();
        app_select = 0; // reset the value
      }
      if(g_deviceConnected == true){
        directions();
      }
      break;
    default:
      if(long_press || short_press){
        short_press = 0; 
        long_press = 0; 
      }
      // Default actions
      break;
  }
  
  if(long_press){ // triggered if long press held
    if(gui_state < 1){
      gui_state = gui_state + 1;
    }else{
      gui_state = 0; 
    }
  }
  short_press = 0; 
  long_press = 0; 
}

