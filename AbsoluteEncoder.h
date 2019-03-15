#ifndef AbsoluteEncoder_h
#define AbsoluteEncoder_h

#include "Arduino.h"

class AbsoluteEncoder {
  public:
    AbsoluteEncoder(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin);
    //float getDegrees(int);  // get the absolute degree
    uint32_t getValue(int);   // get the raw data, 0-4095
    uint32_t readAll(void);   // reads raw data from encoders
  private:
    const uint16_t _clock;  // clock pin: output from arduino to AS5145
    const uint16_t _cs;     // chip select: output
    const uint16_t _data;   // data pin: input
};

#endif
