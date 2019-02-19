#include <Wire.h>

#include "AbsoluteEncoder.h"
#include "VisionSystem.h"

AbsoluteEncoder encoders(3, 6, 7); //data, clock, chip select
VisionSystem visionSystem;

void setup() {
  Wire.begin(10);
  Wire.onRequest(onRequestData);
  Wire.onReceive(onReceiveCommand);

  //Serial.begin(9600); //Serial console for debugging
}

void loop() {
  encoders.readAll();
  visionSystem.readBlocks();

  delay(20);
}

void onRequestData() {
  byte buff[16];

  uint32_t shoulderAngle = encoders.getDegrees(0);
  buff[0] = shoulderAngle >> 24;
  buff[1] = shoulderAngle >> 16;
  buff[2] = shoulderAngle >> 8;
  buff[3] = shoulderAngle;

  uint32_t elbowAngle = encoders.getDegrees(1);
  buff[4] = elbowAngle >> 24;
  buff[5] = elbowAngle >> 16;
  buff[6] = elbowAngle >> 8;
  buff[7] = elbowAngle;

  uint32_t wristAngle = encoders.getDegrees(2);
  buff[8] = wristAngle >> 24;
  buff[9] = wristAngle >> 16;
  buff[10] = wristAngle >> 8;
  buff[11] = wristAngle;

  int targetCenterCoord = visionSystem.getTargetCenterCoord();
  buff[12] = targetCenterCoord >> 8;
  buff[13] = targetCenterCoord;

  int targetWidth = visionSystem.getTargetWidth();
  buff[14] = targetWidth >> 8;
  buff[15] = targetWidth;

  Wire.write(buff, 16);
}

void onReceiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    //Serial.println(command);
  }
}
