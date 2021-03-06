#pragma once
#include "pin.h"
#include "pinsconfig.h"
class Button
{
private:
  IButtonPin& pin; 
public:
  Button(IButtonPin& aPin);
  bool WasPressed();
  void Enable();
};

inline Button button(pinButton);
inline bool flagIndicatorSwitch=false;