#pragma once

#include "led.h" // for Led
#include "pinsconfig.h" // for pinLedX
#include "timer.h"
#include "timercofig.h"
#include "tim2registers.hpp" 
#include "tim3registers.hpp" 
#include "tim4registers.hpp" 
#include "tim5registers.hpp" 
#include "adc.h"
#include "measurer.h"

class LedsIndicator
{
private:
const uint8_t ledsCount=4; 
Led leds[4] = {
                  Led(pinLed1), 
                  Led(pinLed2),
                  Led(pinLed3),
                  Led(pinLed4),
                 };
double dispVal=0;
double dispValMax=adc1.GetRefVoltage();
double dispValMin=0;
ITimer&  timer = tim2;
public:
  void Toggle();
  void UpdateIndicator(double value);
  void UpdateIndicator(double value, double dispValMin, double dispValMax);
  void UpdateIndicator(DispObject& dsp);
  void SetPeriod(uint32_t period); 
  void Enable();
  void Start();
  void Stop();
  double GetDispValue();
  ITimerInterrupted& GetTimer();
};

inline LedsIndicator ledsIndicator;