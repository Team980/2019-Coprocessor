#include <Wire.h>

#include "AbsoluteEncoder.h"
#include "VisionSystem.h"

const int RIODUINO_DEVICE_ADDRESS = 8;

enum Command {
  COMMAND_1,
  COMMAND_2
};

int num;

//AbsoluteEncoder encoders(3, 6, 7);
//VisionSystem visionSystem;

void setup() {
  Wire.begin(RIODUINO_DEVICE_ADDRESS);
  Wire.onRequest(onRequestData);
  Wire.onReceive(onReceiveCommand);

  num = 16384;
}

void loop() {
  //encoders.readAll();
  //visionSystem.readBlocks();

  delay(20);

}


void onRequestData() {
   byte buff[4];

   buff[0] = num >> 24;
   buff[1] = num >> 16;
   buff[2] = num >> 8;
   buff[3] = num;
  
   Wire.write(buff, 4);
}


void onReceiveCommand(int howMany) {
  if (Wire.available() > 0) {
    int c = Wire.read(); // receive int as a enum
  
    num = c;
  }
}
