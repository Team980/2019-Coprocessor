#include "Arduino.h"
#include "VisionSystem.h"

#include <Pixy2.h>

const int VISION_TARGET_SIGNATURE = 1;

Pixy2 pixy;

int distanceBetweenTargets = -1;
int targetCenterCoord = -1;

VisionSystem::VisionSystem() {
  pixy.init();
}

void VisionSystem::readBlocks(void) {
  distanceBetweenTargets = -1;
  targetCenterCoord = -1;

  int numBlocks = pixy.ccc.getBlocks();

  if (numBlocks = 1) {
    Block target = pixy.ccc.blocks[0];
    
    targetCenterCoord = target.m_x;
    
  } else if (numBlocks >= 2) {
    // WARNING: This does not check to make sure they are the correct signature!
    Block largestTarget = pixy.ccc.blocks[0];
    Block secondLargestTarget = pixy.ccc.blocks[1];

    if (VisionSystem::area(secondLargestTarget) > VisionSystem::area(largestTarget)) {
      // Swap the two blocks
      Block _tmp = secondLargestTarget;
      secondLargestTarget = largestTarget;
      largestTarget = _tmp;
    }

    for (int i = 2; i < numBlocks; i++) {
      Block block = pixy.ccc.blocks[i];

      if (block.m_signature == VISION_TARGET_SIGNATURE) {
        if (VisionSystem::area(block) > VisionSystem::area(largestTarget)) {
          secondLargestTarget = largestTarget;
          largestTarget = block;
        } else if (VisionSystem::area(block) > VisionSystem::area(secondLargestTarget)) {
          secondLargestTarget = block;
        }
      }
    }

    distanceBetweenTargets = abs(largestTarget.m_x - secondLargestTarget.m_x);
    targetCenterCoord = (largestTarget.m_x + secondLargestTarget.m_x) / 2;
  }
}

int VisionSystem::getDistanceBetweenTargets() {
  return distanceBetweenTargets;
}

int VisionSystem::getTargetCenterCoord() {
  return targetCenterCoord;
}

int VisionSystem::area(Block b) {
  return b.m_width * b.m_height;
}
