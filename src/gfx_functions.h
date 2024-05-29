
bool init_gfx(){
  // Initial setup of graphics library
  display.begin();
  return true;
}
String mirror_text(String text){
  String mirroredStr = "";
  for (int i = text.length() - 1; i >= 0; i--) {
    mirroredStr += text[i];
  }
  return mirroredStr;
}



void display_clear(){
  display.waitForFrame();
  display.fillScreen(0);
}