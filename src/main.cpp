#include <Arduino.h>
#include "QuickCapTouch.h"

// put function declarations here:
int myFunction(int, int);
QuickCapTouch sensor = QuickCapTouch(27, 30, 1000);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.tick();
  Serial.println(sensor.getState());
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}