#include "Arduino.h"
#include "AbsoluteEncoder.h"

uint32_t rawValues[3];

AbsoluteEncoder::AbsoluteEncoder(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin, uint16_t ProgramInputPin)
           : _data(DataPin), _clock(ClockPin), _cs(ChipSelectPin), _pdio(ProgramInputPin), _pwm(0) {
    pinMode(_data, INPUT);
    pinMode(_clock, OUTPUT);
    pinMode(_cs, OUTPUT);
    pinMode(_pdio, OUTPUT);
}

uint32_t AbsoluteEncoder::getDegrees(int id) {
  return ((encoderValue(id) * 360)/4096);
}

uint32_t AbsoluteEncoder::getValue(int id) {
  return (rawValues[id] >> 6);
}

uint32_t AbsoluteEncoder::readAll(void) {
  rawValues = {0, 0, 0};
  uint16_t inputStream = 0;
  
  digitalWrite(_pdio, LOW);
  digitalWrite(_cs, HIGH);
  digitalWrite(_clock, HIGH);
  digitalWrite(_cs, LOW);
  delayMicroseconds(50);
  
  digitalWrite(_clock, LOW);

  uint16_t i;
  for (i = 0; i < 56; i++) {
    digitalWrite(_clock, HIGH);
    delayMicroseconds(5);
    
    inputStream = digitalRead(_data);

    if (i < 18) {
          rawValues[0] = ((rawValue << 1) + inputStream);
    } else if (i > 18 && i < 37) {
          rawValues[1] = ((rawValues[1] << 1) + inputStream);
    } else if (i > 37 && i < 56) {
          rawValues[2] = ((rawValues[2] << 1) + inputStream);
    }
        
    digitalWrite(_clock, LOW);
    delayMicroseconds(5);
  }
}
