
#include <Arduino.h>
#include <ESP_8_BIT_GFX.h>
#include "defines.h"
#include "gfx_functions.h"
#include "apps.h"
#include "font.h"
#include "mirror_text.h"
#include "esp32notifications.h"




//------------ ANCS Variables ------------//
#define HARDWARE_STANDARD

#ifdef HARDWARE_STANDARD
    #define BUTTON_A    25 // left button - use this GPIO pin
    #define BUTTON_B    26 // center button - use this GPIO pin
    #define BUTTON_C    27 // right button - use this GPIO pin
#else
    #error Hardware buttons not supported!
#endif
// Create an interface to the BLE notification library
BLENotifications notifications;
// Holds the incoming call's ID number, or zero if no notification
uint32_t incomingCallNotificationUUID;
// Device name (What shows up in BLE menu)
const char* device_name = "SigmaSpecula";
// ------------------------------------- // 
void onBLEStateChanged(BLENotifications::State state) {
  switch(state) {
      case BLENotifications::StateConnected:
          Serial.println("StateConnected - connected to a phone or tablet"); 
          break;

      case BLENotifications::StateDisconnected:
          Serial.println("StateDisconnected - disconnected from a phone or tablet"); 
          /* We need to startAdvertising on disconnection, otherwise the ESP 32 will now be invisible.
          IMO it would make sense to put this in the library to happen automatically, but some people in the Espressif forums
          were requesting that they would like manual control over re-advertising.*/
          notifications.startAdvertising(); 
          break; 
  }
}
// A notification arrived from the mobile device, ie a social media notification or incoming call.
// parameters:
//  - notification: an Arduino-friendly structure containing notification information. Do not keep a
//                  pointer to this data - it will be destroyed after this function.
//  - rawNotificationData: a pointer to the underlying data. It contains the same information, but is
//                         not beginner-friendly. For advanced use-cases.
void onNotificationArrived(const ArduinoNotification * notification, const Notification * rawNotificationData) {
    Serial.print("Got notification: ");   
    Serial.println(notification->title); // The title, ie name of who sent the message
    Serial.println(notification->message); // The detail, ie "be home for dinner at 7".
    Serial.println(notification->type);  // Which app sent it
    Serial.println(notifications.getNotificationCategoryDescription(notification->category));  // ie "social media"
    Serial.println(notification->categoryCount); // How may other notifications are there from this app (ie badge number)
    if (notification->category == CategoryIDIncomingCall) {
		// If this is an incoming call, store it so that we can later send a user action.
        incomingCallNotificationUUID = notification->uuid;
        Serial.println("--- INCOMING CALL: PRESS A TO ACCEPT, C TO REJECT ---"); 
    }
    else {
        incomingCallNotificationUUID = 0; // Make invalid - no incoming call
    }
}


// A notification was cleared
void onNotificationRemoved(const ArduinoNotification * notification, const Notification * rawNotificationData) {
     Serial.print("Removed notification: ");   
     Serial.println(notification->title);
     Serial.println(notification->message);
     Serial.println(notification->type);  
}


// Standard Arduino function which is called once when the device first starts up
void init_ancs() {
    Serial.println("ESP32-ANCS-Notifications Initiating");
    Serial.println("------------------------------------------");    
    // Set up the BLENotification library
    notifications.begin("BLEConnection device name");
    notifications.setConnectionStateChangedCallback(onBLEStateChanged);
    notifications.setNotificationCallback(onNotificationArrived);
    notifications.setRemovedCallback(onNotificationRemoved);
}

void setup() {
  Serial.begin(9600);
  
  while(!Serial) {
        delay(10);
  }
  Serial.println("ESP32-ANCS-Notifications Example");
  Serial.println("------------------------------------------");    
  // Set up the BLENotification library
  notifications.begin("BLEConnection device name");
  notifications.setConnectionStateChangedCallback(onBLEStateChanged);
  notifications.setNotificationCallback(onNotificationArrived);
  notifications.setRemovedCallback(onNotificationRemoved);


  // uncomment the following line to see ANCS no longer work!
  //init_gfx();
  //display.fillScreen(0);
}

void loop() {
  // delay(200);
  // display_clear();
  // print_mirrored("TESTING 12345",14,100,16, MAGENTA);
  // print_mirrored("TESTING 12345",14,140,8, WHITE);
  if (incomingCallNotificationUUID > 0) {
		// Check to see if the user has pressed an action button
	    if (digitalRead(BUTTON_A) == LOW) {
	      Serial.println("Positive action."); 
	        notifications.actionPositive(incomingCallNotificationUUID);
	    }
	    else if (digitalRead(BUTTON_C) == LOW) {
	      Serial.println("Negative action."); 
	        notifications.actionNegative(incomingCallNotificationUUID);
	    }
    }
}
