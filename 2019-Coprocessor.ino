#include <Wire.h>

#include "AbsoluteEncoder.h"
//#include "VisionSystem.h"

AbsoluteEncoder encoders(3, 4, 5); //data, clock, chip select
//VisionSystem visionSystem;

void setup() {
  Wire.begin(10);
  Wire.onRequest(onRequestData);
  Wire.onReceive(onReceiveCommand);

  //Serial.begin(9600); //Serial console for debugging
}

void loop() {
  encoders.readAll();
  //visionSystem.readBlocks();

  //delay(20);
}

void onRequestData() {
  byte buff[16];

  uint32_t shoulderValue = encoders.getValue(0);
  buff[0] = shoulderValue >> 24;
  buff[1] = shoulderValue >> 16;
  buff[2] = shoulderValue >> 8;
  buff[3] = shoulderValue;

  uint32_t elbowValue = encoders.getValue(1);
  buff[4] = elbowValue >> 24;
  buff[5] = elbowValue >> 16;
  buff[6] = elbowValue >> 8;
  buff[7] = elbowValue;

  uint32_t wristValue = encoders.getValue(2);
  buff[8] = wristValue >> 24;
  buff[9] = wristValue >> 16;
  buff[10] = wristValue >> 8;
  buff[11] = wristValue;;

  int targetCenterCoord = 4; //visionSystem.getTargetCenterCoord();
  buff[12] = targetCenterCoord >> 8;
  buff[13] = targetCenterCoord;

  int targetWidth = 4; //visionSystem.getTargetWidth();
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
