#include "AbsoluteEncoder.h"

AbsoluteEncoder encoders(3, 6, 7);

void setup() {
  Serial.begin(9600);
}

void loop() {
  encoders.readAll();

  Serial.print("encoder 1: ");
  Serial.println(encoders.getDegrees(0));

  Serial.print("encoder 2: ");
  Serial.println(encoders.getDegrees(1));

  Serial.print("encoder 3: ");
  Serial.println(encoders.getDegrees(2));

  delay(20);
}
