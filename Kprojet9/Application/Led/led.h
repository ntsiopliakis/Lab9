#pragma once
#include "pin.h"

class Led
{
private:
  ILedPin& pin; 
public:
  Led(ILedPin& aPin);
  void Toggle();
  void TurnOn();
  void TurnOff();
  void Enable();
};