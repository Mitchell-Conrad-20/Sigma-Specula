/*
  Use: initialize the ESP_8bit
*/ 
void init_gfx(){
  // Initial setup of graphics library
  display.begin();
}
/*
  Use: Reverse a text string for a mirrored display
*/ 
String mirror_text(String text){
  String mirroredStr = "";
  for (int i = text.length() - 1; i >= 0; i--) {
    mirroredStr += text[i];
  }
  return mirroredStr;
}
/*
  Use: Clear the display 
*/
void display_clear(){
  display.waitForFrame();
  display.fillScreen(0);
}