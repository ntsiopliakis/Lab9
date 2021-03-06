#include "Garlands.h" //for Garlands
#include "timer.h"


void Garlands::Enable()
{ 
  button.Enable();
  for (auto it: leds)
  {
    it.Enable();
  }
  timer.Enable();
  timer.SetPeriod(50);
}

void Garlands::Toggle()
{
  for (auto it: leds)
  {
    it.Toggle();
  }
}

void Garlands::Switch()
{
  static uint8_t counterLedNum=1;

    switch(counterLedNum)
    {
    case 1:
      leds[0].Toggle();
      break;
    case 2:
      leds[1].Toggle();
      break;
    case 3:
      leds[2].Toggle();
      break;
    case 4:
      leds[3].Toggle();
      break;
    case 5:
      leds[3].Toggle();
      break;
    case 6:
      leds[2].Toggle();
      break;
    case 7:
      leds[1].Toggle();
      break;
    case 8:
      leds[0].Toggle();
      break;
    }
    counterLedNum=(counterLedNum<8)?(counterLedNum+1):1;
}

void Garlands::SetPeriod(uint32_t period)
{
  timer.SetPeriod(period);
}
bool Garlands::ButtonPressed()
{
  return button.WasPressed();
}

void Garlands::PeriodUpdate()
{
  static bool periodDirection =1;
  static uint16_t period = 50;
      if(period==1000)
      {
        periodDirection=0;
      }
      if(period==50)
      {
        periodDirection=1;
      }

      if(periodDirection)
      {
        period+=50;
      }
      else
      {
        period-=50;
      }

      garlands.SetPeriod(period);
}

void Garlands::Start()
{
  timer.Start();
}
void Garlands::Stop()
{
  timer.Stop();
}