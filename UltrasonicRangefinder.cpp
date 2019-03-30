#include "Arduino.h"
#include "UltrasonicRangefinder.h"

#include <SoftwareSerial.h>

SoftwareSerial serial(4, 5, true); //Yes, I know this isn't parameterized

int range;

UltrasonicRangefinder::UltrasonicRangefinder() {
  serial.begin(9600);
}

void UltrasonicRangefinder::readData() {
  boolean msgComplete = false;
  int index = 0;
  char buff[3];

  noInterrupts(); //TODO do we need this?

  serial.flush();

  while (!msgComplete) {
    if (serial.available()) {
      char headerByte = serial.read();
      if (headerByte == 'R') {
        while (index < 3) {
          if (serial.available()) {
            buff[index] = serial.read();
            index++;
          }
        }
        buff[index] = 0x00;
      }
      headerByte = 0;

      index = 0;
      msgComplete = true;
    }
  }

  range = atoi(buff);
  
  interrupts(); //TODO

}

int UltrasonicRangefinder::getRange() {
  return range;
}
