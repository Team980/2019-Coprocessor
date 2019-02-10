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

  int targetCenterCoord = visionSystem.getTargetCenterCoord();
  buff[0] = targetCenterCoord >> 8;
  buff[1] = targetCenterCoord;

  int targetWidth = visionSystem.getTargetWidth();
  buff[2] = targetWidth >> 8;
  buff[3] = targetWidth;

  Wire.write(buff, 4);
}

void onReceiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    Serial.println(command);
  }
}
