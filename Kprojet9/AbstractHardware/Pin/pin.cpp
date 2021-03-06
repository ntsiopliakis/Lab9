#include "pin.h" //for Pin



Pin::Pin(uint8_t aNumber, IPort& aPort): number(aNumber), 
                                         port(aPort)
{
}

void Pin::Toggle()
{
  port.Toggle(number);
}
void Pin::Set()
{
     port.Set(1<<number);
}
void Pin::Reset()
{
     port.Reset(1<<number);
}
bool Pin::IsSet()
{
  return port.IsSet(number);
}
uint8_t Pin::Get()
{
  return Pin::IsSet()?1U:0U;
}
void Pin::Enable()
{
  if(!port.IsEnable())port.Enable();
}
void Pin::SelectInputMode()
{
  port.ModeSet(number,Moder::Input);
}
void Pin::SelectOutputMode()
{
  port.ModeSet(number,Moder::Output);
}
void Pin::SelectMode(Moder moder)
{
  port.ModeSet(number,moder);
}