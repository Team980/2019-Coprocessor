#ifndef UltrasonicRangefinder_h
#define UltrasonicRangefinder_h

#include "Arduino.h"

class UltrasonicRangefinder {
  public:
    UltrasonicRangefinder();
    void readData();
    int getRange();
};

#endif
