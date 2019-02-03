#include <Wire.h>

//#include "AbsoluteEncoder.h"
//#include "VisionSystem.h"

//AbsoluteEncoder encoders(3, 6, 7);
//VisionSystem visionSystem;

int data;

void setup() {
  Wire.begin(10);
  Wire.onRequest(onRequestData);
  Wire.onReceive(onReceiveCommand);

  data = 618;

  Serial.begin(9600);
}

void loop() {
  //encoders.readAll();
  //visionSystem.readBlocks();

  delay(20);
}

void onRequestData() {
  byte buff[2];

  buff[0] = data >> 8;
  buff[1] = data;

  Wire.write(buff, 2);
}

void onReceiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    if (command != 0) {
      Serial.println(command);
    }
  }
}
