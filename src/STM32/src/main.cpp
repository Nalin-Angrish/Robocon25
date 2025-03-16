#include <Arduino.h>
#include <Encoder.hpp>

Encoder encoder(PA0, PA1);

void setup() {
  // put your setup code here, to run once:
  encoder.begin();
  Serial1.begin(115200);
  pinMode(PC13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.println(encoder.getValue());
  digitalWrite(PC13, HIGH);
  delay(200);
  digitalWrite(PC13, LOW);
  delay(200);
}