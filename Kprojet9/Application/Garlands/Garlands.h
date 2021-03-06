#pragma once

#include "led.h" // for Led
#include "pinsconfig.h" // for pinLedX
#include "Button.h"
#include "timer.h"
#include "timercofig.h"
#include "tim2registers.hpp" 
#include "tim3registers.hpp" 
#include "tim4registers.hpp" 
#include "tim5registers.hpp" 

class Garlands
{
private: 
  Led leds[4] = {
                  Led(pinLed1), 
                  Led(pinLed2),
                  Led(pinLed3),
                  Led(pinLed4),
                 };
  Button button = Button(pinButton);
  ITimer&  timer = tim2 ;
public:
  void Toggle();
  void Switch();
  void SetPeriod(uint32_t period); 
  bool ButtonPressed();
  void PeriodUpdate();
  void Enable();
  void Start();
  void Stop();
};
inline Garlands garlands;