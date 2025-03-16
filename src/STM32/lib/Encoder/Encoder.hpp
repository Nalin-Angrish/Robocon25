#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <functional>

class Encoder
{
private:
  int pinA, pinB;
  int encodedValue;
  int lastEncodedValue;

  std::function<void ()> getInterruptHandler();
public:
  Encoder(int pinA, int pinB);
  void begin();
  long getValue();
  ~Encoder();
};

#endif // ENCODER_HPP