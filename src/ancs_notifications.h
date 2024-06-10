 


// ------------------------------------- // 
// Standard Arduino function which is called once when the device first starts up
void stop_ancs() {
  notifications.stop();
  BLEDevice::deinit();
  Serial.println("ANCS is turned off!");
}
void onBLEStateChanged(BLENotifications::State state) {
  switch (state) {
    case BLENotifications::StateConnected:
      Serial.println("StateConnected - connected to Glass");
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
void init_ancs() {
    Serial.println("ESP32-ANCS-Notifications Initiating");
    Serial.println("------------------------------------------");    
    // Set up the BLENotification library
    notifications.begin(device_name);
    notifications.setConnectionStateChangedCallback(onBLEStateChanged);
    notifications.setNotificationCallback(onNotificationArrived);
    notifications.setRemovedCallback(onNotificationRemoved);
}
void accept_incoming_call(){
    Serial.println("Receiving Call!"); 
    notifications.actionPositive(incomingCallNotificationUUID);
}
void deny_incoming_call(){
    Serial.println("Denying Call!"); 
    notifications.actionNegative(incomingCallNotificationUUID);
}

 
 