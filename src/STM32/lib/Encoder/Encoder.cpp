#include <Arduino.h>
#include <Encoder.hpp>

Encoder::Encoder(int pinA, int pinB)
{
  this->encodedValue = 0;
  this->lastEncodedValue = 0;
  this->pinA = pinA;
  this->pinB = pinB;
}

void Encoder::begin()
{
  pinMode(this->pinA, INPUT_PULLUP);
  pinMode(this->pinB, INPUT_PULLUP);

  digitalWrite(this->pinA, HIGH);
  digitalWrite(this->pinB, HIGH);

  attachInterrupt(digitalPinToInterrupt(this->pinA), this->getInterruptHandler(), CHANGE);
  attachInterrupt(digitalPinToInterrupt(this->pinB), this->getInterruptHandler(), CHANGE);
}

std::function<void ()> Encoder::getInterruptHandler()
{
  return [this]() {
    int MSB = digitalRead(this->pinA);
    int LSB = digitalRead(this->pinB);

    int encoded = (MSB << 1) | LSB;
    int sum = (this->lastEncodedValue << 2) | encoded;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    {
      this->encodedValue++;
    }
    else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    {
      this->encodedValue--;
    }

    this->lastEncodedValue = encoded;
  };
}

long Encoder::getValue()
{
  return this->encodedValue;
}

Encoder::~Encoder()
{
}
