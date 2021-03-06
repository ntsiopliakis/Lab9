#include "ledsIndicator.h"
#include "timer.h"
#include "adc.h"


void LedsIndicator::Enable()
{ 
  for (auto it: leds)
  {
    it.Enable();
  }
  timer.Enable();
  timer.SetPeriod(50);
}

void LedsIndicator::SetPeriod(uint32_t period)
{
  timer.SetPeriod(period);
}

void LedsIndicator::UpdateIndicator(double value)
{
  dispVal=value;
  for(int i=0;i<ledsCount;i++)
  {
    if(dispVal>(0.5+i)*dispValMax/ledsCount)
    {
      leds[i].TurnOn();
    }
    else
    {
      leds[i].TurnOff();
    }
  } 
}

void LedsIndicator::UpdateIndicator(double value,double dispValMin1, double dispValMax1)
{
  dispValMax=dispValMax1;
  dispValMin=dispValMin1;
  dispVal=value;
  for(int i=0;i<ledsCount;i++)
  {
    if((dispVal-dispValMin)>(0.5+i)*(dispValMax-dispValMin)/ledsCount)
    {
      leds[i].TurnOn();
    }
    else
    {
      leds[i].TurnOff();
    }
  } 
}
void LedsIndicator::UpdateIndicator(DispObject& dsp)
{
  dispValMax=dsp.GetMaxValue();
  dispValMin=dsp.GetMinValue();
  dispVal=dsp.GetValue();
  for(int i=0;i<ledsCount;i++)
  {
    if((dispVal-dispValMin)>(0.5+i)*(dispValMax-dispValMin)/ledsCount)
    {
      leds[i].TurnOn();
    }
    else
    {
      leds[i].TurnOff();
    }
  } 
}

void LedsIndicator::Start()
{
  timer.Start();
}
void LedsIndicator::Stop()
{
  timer.Stop();
  for (auto it: leds)
  {
    it.TurnOff();
  }
}

ITimerInterrupted& LedsIndicator::GetTimer()
{
  return timer;
}


double LedsIndicator::GetDispValue()
{
  return dispVal;
}