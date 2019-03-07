#include "Arduino.h"
#include "AbsoluteEncoder.h"

uint32_t rawValues[3];

AbsoluteEncoder::AbsoluteEncoder(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin)
  : _data(DataPin), _clock(ClockPin), _cs(ChipSelectPin) {
  pinMode(_data, INPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_cs, OUTPUT);

  digitalWrite(_cs, HIGH);
  digitalWrite(_clock, HIGH);
}

uint32_t AbsoluteEncoder::getDegrees(int id) {
  return ((getValue(id) * 360) / 4096);
}

uint32_t AbsoluteEncoder::getValue(int id) {
  return (rawValues[id] >> 6);
}

uint32_t AbsoluteEncoder::readAll(void) {
  rawValues[0] = 0;
  rawValues[1] = 0;
  rawValues[2] = 0;

  uint16_t inputStream = 0;

  noInterrupts();

  digitalWrite(_cs, LOW);
  digitalWrite(_clock, LOW);
  delayMicroseconds(1);

  int i;
  for (i = 0; i < 57; i++) {
    digitalWrite(_clock, HIGH);
    delayMicroseconds(1);

    inputStream = digitalRead(_data);

    if (i < 18) {
      rawValues[0] = ((rawValues[0] << 1) + inputStream);
    } else if (i > 18 && i < 37) {
      rawValues[1] = ((rawValues[1] << 1) + inputStream);
    } else if (i > 37 && i < 56) {
      rawValues[2] = ((rawValues[2] << 1) + inputStream);
    }

    digitalWrite(_clock, LOW);
    delayMicroseconds(1);
  }

  digitalWrite(_cs, HIGH);
  digitalWrite(_clock, HIGH);

  interrupts();
}
