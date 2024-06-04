/*
  Use: Draw a char from a bitmap pixel by pixel at point (x,y) for x font size
*/ 
void drawChar(const uint8_t *charBitmap, int x, int y, int font_size, uint16_t color) {
  for (int row = 0; row < font_size; row++) {
    for (int col = 0; col < font_size; col++) {
      bool pixelOn = charBitmap[row] & (1 << col);
      if (pixelOn) {
        display.drawPixel(x + col, y + row, color); // Change to x + col
      }
    }
  }
}
/*
  Use: Draw a mirrored char from a bitmap pixel by pixel at point (x,y) for x font size
*/ 
void drawMirroredChar(const uint8_t *charBitmap, int x, int y, int font_size, uint16_t color) {
  for (int row = 0; row < font_size; row++) {
    for (int col = font_size - 1; col >= 0; col--) {  // Iterate in reverse order
      bool pixelOn = charBitmap[row] & (1 << col);
      if (pixelOn) {
        display.drawPixel(x + (font_size - 1 - col), y + row, color);  // Change to x + (font_size - 1 - col)
      }
    }
  }
}
/*
  Use: Print a mirrored string at point (x,y)
*/
void print_mirrored(String myString, int x, int y, int size, uint16_t color = WHITE) {
    const char* characters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int startX = x-size;
    int startY = y-size;
    int char_spacing = 0; // how much space to place between chars (depends on font)
    int space = 0;
    switch (size) {
    case 8:
        char_spacing = 8;
        space = 4;
        break;
    case 16:
        char_spacing = 10;
        space = 4;
        break;
    default:
        Serial.println("Text Size Error!");
        break;
    }
    for (int i = myString.length() - 1; i >= 0; i--) {
        char myChar = myString.charAt(i);
        if (myChar == ' ') {
            startX = startX + space; // Add space for space character
            continue;
        }
        for (int j = 0; j < sizeof(characters) / sizeof(characters[0]); j++) {
            if (characters[j][0] == myChar) {
                startX = startX + char_spacing;
                if(size == 8){
                  drawMirroredChar(numbers_8[j], startX, startY, size, color);
                }
                if(size == 16){
                  drawMirroredChar(numbers_16[j], startX, startY, size, color);
                }
                break;
            }
        }
    }
}
/*
  Use: Debugging function to show all numbers and letters in the bitmaps
*/
void displayMirroredTextDebug() {
  int startX = 50;
  int startY = 100;
  int spacing = 20; // Adjust as needed
  int numbers_8_len = sizeof(numbers_8) / sizeof(numbers_8[0]);
  int sleep = 200;
  display_clear();
  for (int i = 0; i < numbers_8_len; i++) {
      drawMirroredChar(numbers_16[i], startX, startY, 16, RED);
      drawChar(numbers_16[i], startX+20, startY, 8, MAGENTA);
      delay(sleep); // Delay for visibility, adjust as needed
      display_clear();
      drawMirroredChar(numbers_8[i], startX, startY, 8, GREEN);
      drawChar(numbers_8[i], startX+10, startY, 8, BLUE);
      delay(sleep); // Delay for visibility, adjust as needed
      display_clear();
  }
}