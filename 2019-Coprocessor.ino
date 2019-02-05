#include <Wire.h>

//#include "AbsoluteEncoder.h"
#include "VisionSystem.h"

//AbsoluteEncoder encoders(3, 6, 7);
VisionSystem visionSystem;

void setup() {
  Wire.begin(10);
  Wire.onRequest(onRequestData);
  Wire.onReceive(onReceiveCommand);

  //Serial.begin(9600); //Serial console for debugging
}

void loop() {
  //encoders.readAll();
  visionSystem.readBlocks();

  delay(20);
}

void onRequestData() {
  byte buff[4];
  
  int distanceBetweenTargets = visionSystem.getDistanceBetweenTargets();
  buff[0] = distanceBetweenTargets >> 8;
  buff[1] = distanceBetweenTargets;

  int targetCenterCoord = visionSystem.getTargetCenterCoord();
  buff[2] = targetCenterCoord >> 8;
  buff[3] = targetCenterCoord;

  Wire.write(buff, 4);
}

void onReceiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    Serial.println(command);
  }
}
