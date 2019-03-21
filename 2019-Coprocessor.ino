#include <Wire.h>

#include "AbsoluteEncoder.h"
#include "VisionSystem.h"

// Used to transfer floats over the data bus
typedef union {
    float f;
    char bytes[4];
} packedFloat;

AbsoluteEncoder encoders(3, 4, 5); //data, clock, chip select
VisionSystem visionSystem;

// Used to calculate average velocity of each joint
float valueBuffer[3][2];
float timeBuffer[2];
float velocityBuffer[3];

void setup() {
  Wire.begin(10);
  Wire.onRequest(onRequestData);
  //Wire.onReceive(onReceiveCommand);

  //Serial.begin(9600); //Serial console for debugging
}

void loop() {
  timeBuffer[1] = timeBuffer[0];
  timeBuffer[0] = millis() / 1000.0f;
  
  encoders.readAll();

  valueBuffer[0][1] = valueBuffer[0][0];
  valueBuffer[0][0] = encoders.getValue(0) * (360 / 4096.0f);
  velocityBuffer[0] = (valueBuffer[0][0] - valueBuffer[0][1]) / (timeBuffer[0] - timeBuffer[1]);

  valueBuffer[1][1] = valueBuffer[1][0];
  valueBuffer[1][0] = encoders.getValue(1) * (360 / 4096.0f);
  velocityBuffer[1] = (valueBuffer[1][0] - valueBuffer[1][1]) / (timeBuffer[0] - timeBuffer[1]);

  valueBuffer[2][1] = valueBuffer[2][0];
  valueBuffer[2][0] = encoders.getValue(2) * (360 / 4096.0f);
  velocityBuffer[2] = (valueBuffer[2][0] - valueBuffer[2][1]) / (timeBuffer[0] - timeBuffer[1]);

  //Serial.println(timeBuffer[0] - timeBuffer[1]);
  
  visionSystem.readBlocks();

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

  int targetCenterCoord = visionSystem.getTargetCenterCoord();
  buff[12] = targetCenterCoord >> 8;
  buff[13] = targetCenterCoord;

  int targetWidth = visionSystem.getTargetWidth();
  buff[14] = targetWidth >> 8;
  buff[15] = targetWidth;

  Wire.write(buff, 16);

  packedFloat packedShoulderVel;
  packedShoulderVel.f = velocityBuffer[0];

  Wire.write(packedShoulderVel.bytes, 4);

  packedFloat packedElbowVel;
  packedElbowVel.f = velocityBuffer[1];

  Wire.write(packedElbowVel.bytes, 4);

  packedFloat packedWristVel;
  packedWristVel.f = velocityBuffer[2];

  Wire.write(packedWristVel.bytes, 4);
}

/*void onReceiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    //Serial.println(command);
  }
}*/
