#ifndef VisionSystem_h
#define VisionSystem_h

#include "Arduino.h"

#include <Pixy2.h>

class VisionSystem {
  public:
    VisionSystem();
    void readBlocks(void);
    int getDistanceBetweenTargets();
    int getTargetCenterCoord();
  private:
    int area(Block b);
};

#endif
