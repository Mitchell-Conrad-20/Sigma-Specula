#include "CapacitiveTouch.h"

/*************** REFERENCES ***************/
// The following repository was a source of inspiration for this project
// It did not meet my needs as it was not compatible with the board I was using, but it may meet yours
// https://github.com/PaulStoffregen/CapacitiveSensor/blob/master/CapacitiveSensor.cpp
// My source code is very different in many ways, and similar in others

/*************** USAGE ***************/
// Wire a 10 M-Ohm resister between the input and output pins
// Connect a wire to the input pin. This can be your sensor or can connect to another conductor
// Set the samples value. Typical value is 30
// Set the threshold value. Typical value is 1000
// Do not touch the sensor on startup. The sensor briefly calibrates (ms)

CapacitiveTouch::CapacitiveTouch(uint8_t input_pin, uint8_t output_pin, uint8_t samples, int threshold)
  : input_pin(input_pin), output_pin(output_pin), samples(samples), threshold(threshold) {
  
  // Set Pin Modes
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, LOW);
  pinMode(input_pin, INPUT);

  // Set state to 0
  state = 0;

  calibration_val = 0;

  // Calibrate
  calibrate();
}

int CapacitiveTouch::getState(){
  return state;
}

// Tick returns a debounced value for if the sensor was just touched
// 0 = no touch, 1 = touch
int CapacitiveTouch::tick() {
  int new_state = read() > threshold;

  if (state == 0){
    state = new_state;
    return state;
  }
  else if (new_state == 0){
    state = 0;
  }

  return 0;
}

// Read
int CapacitiveTouch::read() {
  int total = 0;

  // Send a 10ms pulse to the digital output
  digitalWrite(output_pin, HIGH);
  delay(10);
  digitalWrite(output_pin, LOW);

  for (uint8_t i = 0; i < samples; i++) {
    total += analogRead(input_pin);
  }

  total -= calibration_val;
  total /= samples;
  
  return total;
}

// Calibrate
void CapacitiveTouch::calibrate() {
  long offset = 0;

  // Send a 10ms pulse to the digital output
  digitalWrite(output_pin, HIGH);
  delay(10);
  digitalWrite(output_pin, LOW);

  // Summation
  for (uint8_t i = 0; i < samples; i++) {
    offset += analogRead(input_pin);
  }

  // Set the calibration value
  calibration_val = offset;
}