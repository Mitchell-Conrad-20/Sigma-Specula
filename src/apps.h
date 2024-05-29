void draw_debug(){
    // draw vertical (Y) pixel position bar 
    for (int y = 0; y < display.height(); y += 8) {
        display.drawLine(0, y, 15, y, GREEN); // Draw horizontal tick
        display.setCursor(0, y);
        display.setTextColor(WHITE);
        display.setTextSize(1); // Set text size to 1 (smallest)
        display.print(y); // Print the pixel number
    }
    // draw horizontal (X) pixel position bar 
    for (int x = 0; x < display.width(); x += 4) {
        String x_str = String(x);
        x = x + (4*x_str.length());
        display.drawLine(x, 0, x, 25, GREEN); // Draw horizontal tick
        display.setCursor(x, 15);
        display.setTextColor(WHITE);
        display.setTextSize(1); // Set text size to 1 (smallest)
        display.print(x); // Print the pixel number
    }

}

void main_app_screen(){
    display_clear();
    int x = int(9*(display.width()/14));
    int y = int(5*(display.height()/8));
    display.drawRoundRect(36,36,202-36,208-36,15,RED);
    draw_debug();
     
    display.setTextSize(3); // Set text size to 1 (smallest)
    display.setTextColor(CYAN);
    display.setCursor(50, 52);
    display.println("12:09 PM");
    display.setTextSize(2); // Set text size to 1 (smallest)
    display.setTextColor(GREEN);
    display.setCursor(50, 80);
    display.println("11/24/24");
    display.setCursor(154, 80);
    display.println("THU");
    display.setTextSize(2);
    display.setTextColor(YELLOW);
    display.setCursor(50, 108);
    display.println("37");
    display.setTextSize(1);
    display.setCursor(72+4, 106);
    display.println("O");
}