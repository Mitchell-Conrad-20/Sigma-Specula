
void timeConvert(String message) {
  int day = 0; 
  int month = 0;
  int year = 0; 
  int hour = 0;
  int minute = 0;
  int second = 0;
  String pmam = "";
  
  

  // Remove the initial part of the message
  message.remove(0, 7);

  // Find the location of the first '!'
  int break1 = message.indexOf('!');
  
  // Extract and convert temperature
  temperature_val = int(message.substring(0, break1).toFloat());
  
  // Remove the processed part of the message
  message.remove(0, break1 + 1);

  // Parse the remaining string for date, time, and weather information
  const char* stringMess = message.c_str();
  Serial.println(stringMess);
  sscanf(stringMess, "%d-%d-%d %d:%d:%d|%s !%s!", &day, &month, &year, &hour, &minute, &second, pmam.c_str(), weather.c_str());
  // Find the '|' and '!' positions to extract pmam and weather
  break1 = message.indexOf('|');
  int break2 = message.indexOf('!', break1 + 1);
  pmam = message.substring(break1 + 1, break2);

  message.remove(0, break2 + 1);
  break1 = message.indexOf('!');
  weather = message.substring(0, break1);
  weather.toLowerCase();

  // Adjust hour based on PM/AM
  if (pmam == "PM" && hour < 12) {
    hour += 12;
  } else if (pmam == "AM" && hour == 12) {
    hour = 0;
  }

  //Print parsed values for debugging
  Serial.print(hour); Serial.print(":");
  Serial.print(minute); Serial.print(":");
  Serial.print(second); Serial.print(", ");
  Serial.print(day); Serial.print("/");
  Serial.print(month); Serial.print("/");
  Serial.print(year); Serial.print(", ");
  Serial.print("Temperature: "); Serial.println(temperature_val);
  Serial.println("Weather:" + weather);

  // Set time (assume rtc.setTime is a valid function)
  rtc.setTime(second, minute, hour, day, month, year);  // Set RTC time
  
  delay(100);
  Serial.println(rtc.getTimeDate(true));
  Serial.println("Temperature is: " + String(temperature_val));
  display_flag = true; // reset the display with the new values 
}



 
 
void stop_ancs() {
  notifications.stop();
  Serial.println("ANCS is turned off!");
  delay(50);
}
void onBLEStateChanged(BLENotifications::State state) {
  switch (state) {
    case BLENotifications::StateConnected:
      // Reset list of notifications
      notifList.reset();
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
    if (notification->message.indexOf("Zephr21") >= 0) { /// init for time conversion
      timeConvert(String(notification->message));
    }else{
      Serial.print("Got notification: ");   
      Serial.println(notification->title); // The title, ie name of who sent the message
      Serial.println(notification->message); // The detail, ie "be home for dinner at 7".
      Serial.println(notification->type);  // Which app sent it
      Serial.println(notifications.getNotificationCategoryDescription(notification->category));  // ie "social media"
      Serial.println(notification->categoryCount); // How may other notifications are there from this app (ie badge number)
      notifList.addNotification(rawNotificationData);
    }
    
}
// A notification was cleared
void onNotificationRemoved(const ArduinoNotification * notification, const Notification * rawNotificationData) {
     Serial.print("Removed notification: ");   
     Serial.println(notification->title);
     Serial.println(notification->message);
     Serial.println(notification->type);  
     notifList.removeNotification(rawNotificationData);
}
void init_ancs() {
    Serial.println("ESP32-ANCS-Notifications Initiating");
    Serial.println("------------------------------------------");    
    // Set up the BLENotification library
    notifications.begin(device_name);
    notifications.setConnectionStateChangedCallback(onBLEStateChanged);
    notifications.setNotificationCallback(onNotificationArrived);
    notifications.setRemovedCallback(onNotificationRemoved);
    incomingCallNotificationUUID = 0;
}
void accept_incoming_call(){
    Serial.println("Receiving Call!"); 
    notifications.actionPositive(incomingCallNotificationUUID);
}
void deny_incoming_call(){
    Serial.println("Denying Call!"); 
    notifications.actionNegative(incomingCallNotificationUUID);
}

