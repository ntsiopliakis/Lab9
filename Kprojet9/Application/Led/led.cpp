#include "led.h"


Led::Led(ILedPin& aPin): pin(aPin)
{
}

void Led::Toggle()
{
  pin.Toggle();
}
void Led::TurnOn()
{
  pin.Set();
}
void Led::TurnOff()
{
  pin.Reset();
}

void Led::Enable()
{
  pin.Enable();
  pin.SelectOutputMode();
}