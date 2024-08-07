
void turn_on_display(){
  u8g2.setPowerSave(0);
}
void turn_off_display(){
  u8g2.setPowerSave(1);
}
void draw_home() {
    String time = rtc.getTime();
    print("DRAW HOME: " + time + " | " + "Temperature: " + String(temperature_val));
    time = time.substring(0, time.length() - 3);
    String temperature = String(temperature_val);
    u8g2.clearBuffer();	
    u8g2.drawRFrame(0,0,displayWidth,displayHeight,7);
    u8g2.setFont(u8g2_font_u8glib_4_tf);	// choose a suitable font

    // Set font direction and flip mode if needed
    u8g2.setFontDirection(1); // Set font direction to vertical (90 degrees clockwise)
    u8g2.setFlipMode(2); // Keep normal mode

    //---------------------------------------- Draw Time ----------------------------------------------// 
    // Calculate position to center the string at the top
    int x = displayWidth-15;
    int y = displayHeight / 2 - (u8g2.getStrWidth(time.c_str()) / 2); // Use ascent to position at the top
    u8g2.drawStr(x, y, time.c_str());	// write the rotated string to the internal memory
    
    // -------------------------------------- Draw Temperature ---------------------------------------// 
    
    u8g2.setFont(u8g2_font_tiny5_tf);
    // Calculate position to center the temperature string in the middle
    int tempX = displayWidth-25;
    int tempY = displayHeight / 2 - (u8g2.getStrWidth(temperature.c_str()) / 2); // Use ascent to position at the top

    u8g2.drawStr(tempX, tempY, temperature.c_str());
    u8g2.drawGlyph(tempX + u8g2.getStrWidth(temperature.c_str())-5, tempY+8, 0x00B0); // Draw degree symbol

    u8g2.setBitmapMode(false /* solid */);
    int hour = rtc.getHour(true);  // Get the hour in 24-hour format

    if (hour >= 20 || hour < 6) {
      u8g2.drawXBMP(12, 7, 19, 19, moon);
    } else {
      if (weather.indexOf("sun") >= 0) {
        u8g2.drawXBMP(12, 7, 19, 19, sun);
      }else{
        u8g2.drawXBMP(12, 7, 19, 19, rain);
      }
    }

    
    
   
 
    u8g2.sendBuffer();					// transfer internal memory to the display



}
void draw_message(String sender, String message) {
    // Clear the display buffer
    u8g2.clearBuffer();

    // Draw a rounded frame around the display
    u8g2.drawRFrame(0, 0, displayWidth, displayHeight, 7);

    // Set the font for the sender's name
    u8g2.setFont(u8g2_font_u8glib_4_tf);

    // Set font direction and flip mode if needed
    u8g2.setFontDirection(1); // Set font direction to vertical (90 degrees clockwise)
    u8g2.setFlipMode(2); // Keep normal mode

    // Draw the sender's name at the top of the display
    u8g2.drawStr(displayWidth - 8, 5, sender.substring(0, 6).c_str());
    u8g2.drawLine(displayWidth - 10, 0, displayWidth - 10, displayHeight);

    // Set the font for the message content
    u8g2.setFont(u8g2_font_u8glib_4_tf);

    // Define vertical text settings
    int lineHeight = 8; // Adjust based on your font size
    int yPosition = 3; // Start below the sender's name
    int xPosition = displayWidth - 17; // Adjust as needed
    int displayHeight = 60;
    // Draw the message content below the sender's name, rotated 90 degrees
    int maxCharsPerColumn = (displayHeight / u8g2.getMaxCharWidth());

    // Split the message into segments that fit the display height
    while (message.length() > 0 && xPosition < displayWidth) {
        String segment = message.substring(0, maxCharsPerColumn);
        message = message.substring(maxCharsPerColumn);
        u8g2.drawStr(xPosition, yPosition, segment.c_str());
        xPosition -= lineHeight;
    }

    // Transfer internal memory to the display
    u8g2.sendBuffer();
}
void draw_bitmap(){
   u8g2.clearBuffer();
   u8g2.drawXBMP(12, 3, 24, 24, round_about);
   u8g2.sendBuffer();
}
void draw_navigation_command(String command, String distance, String speed = "10"){
  
  u8g2.clearBuffer();
  u8g2.drawRFrame(0,0,displayWidth,displayHeight,7);
  u8g2.setFont(u8g2_font_tiny5_tf);	// choose a suitable font
  // Set the display to flip mode
  u8g2.setFlipMode(3);
  // Rotate the string 90 degrees
  u8g2.setFontDirection(1);
  //---------------------------------------- Speed ----------------------------------------------// 
  speed += "MPH"; 
  // Calculate position to center the string at the top
  int x = displayWidth-15;
  int y = displayHeight / 2 - (u8g2.getStrWidth(speed.c_str()) / 2); // Use ascent to position at the top
  u8g2.drawStr(x, y, (speed).c_str());	// write the rotated string to the internal memory
  //---------------------------------------- Symbol----------------------------------------------// 
  int x_XB = 23;
  int y_XB = 4;
  Serial.println("Draw command: " + String(command));// + " | " distance + " | " +  speed);
  if(command.indexOf("Right") != -1){    
    Serial.println("Drawing right!");
    u8g2.drawXBMP(x_XB, y_XB, 24, 24, right_arrow);
  }
  if(command.indexOf("Left") != -1){   
    u8g2.drawXBMP(x_XB, y_XB, 24, 24, left_arrow);
  }
  if(command.indexOf("Round") != -1){
    u8g2.drawXBMP(x_XB, y_XB, 24, 24, round_about);
  }
  if(command.indexOf("None") != -1 or command.indexOf("End") != -1){
    u8g2.drawXBMP(x_XB, y_XB, 24, 24, end);
  }
  if(command.indexOf("Follow") != -1 or command.indexOf("Straight") != -1 or command.indexOf("Via") != -1){
    u8g2.drawXBMP(x_XB, y_XB, 24, 24, forward_arrow);
  }
  //---------------------------------------- Distance ----------------------------------------------// 
  // Calculate position to center the temperature string in the middle
  int tempX = displayWidth-48;
  int tempY = displayHeight / 2 - (u8g2.getStrWidth(distance.c_str()) / 2); // Use ascent to position at the top

  u8g2.drawStr(tempX, tempY, distance.c_str());
  u8g2.sendBuffer();
}
void debug(){
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_u8glib_4_tf);	// choose a suitable font

  // Set the display to flip mode
  u8g2.setFlipMode(1);
  //u8g2.setFontDirection(3);
  u8g2.drawStr(0, 5, "Hello,");	 // write something to the internal memory
  u8g2.drawStr(0, 10, "World…");
  u8g2.drawStr(0, 15, "I'm tiny…");
  u8g2.drawStr(0, 20, "So tiny!");
  u8g2.drawStr(0, 25, "However you can");
  u8g2.drawStr(0, 30, "have six lines");

  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(1000);
}
void draw_app(int i){
  if(i == 0){
    u8g2.clearBuffer();
    u8g2.drawXBMP(10, 1, 50, 30, navigation);
    u8g2.sendBuffer();
  }else if(i == 1){
    u8g2.clearBuffer();
    u8g2.drawXBMP(20, 1, 30, 30, sms);
    u8g2.sendBuffer();
  }else{
    u8g2.clearBuffer();
    u8g2.drawXBMP(23, 4, 24, 24, left_arrow);
    u8g2.sendBuffer();
  }
}