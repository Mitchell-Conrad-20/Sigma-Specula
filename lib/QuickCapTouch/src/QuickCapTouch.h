#ifndef QUICKCAPTOUCH_H
#define QUICKCAPTOUCH_H

#include <Arduino.h>

class QuickCapTouch {
  public:
    // Constructor
    QuickCapTouch(uint8_t input_pin, uint8_t samples, int threshold);

    // Read - Reads the analog value. Typically only required for internal use
    // Can be useful for doing additional processing outside of the library (ex: pressure clicks)
    int read();

    // Tick - Returns 1 if the sensor was pressed on this tick, else returns 0
    int tick();

    // Get State - Returns the value of the state member
    int getState();

  private:
    // Variables
    uint8_t input_pin;
    uint8_t samples;
    int threshold;
    uint8_t state;
    long calibration_val;

    // Methods
    void calibrate();
};

#endif // QUICKCAPTOUCH_H