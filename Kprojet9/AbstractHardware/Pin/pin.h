#pragma once
#include <cstdint> // for uint8_t
#include "port.h"  // for IPort 

class ILedPin
{
public:  
  virtual void Toggle() = 0;
  virtual void Set()=0;
  virtual void Reset()=0;
  virtual void SelectOutputMode()= 0;
  virtual void Enable()=0;
};
class IButtonPin
{
public:  
  virtual bool IsSet() = 0; 
  virtual void SelectInputMode()=0;
  virtual void Enable()=0;
};

class Pin: public IButtonPin, public ILedPin
{
private:
  uint8_t number;
  IPort& port;
  
public: 
   Pin(uint8_t aNumber, IPort& aPort);
   void Toggle() override;
   void Set() override;
   void Reset() override;
   uint8_t Get();
   bool IsSet() override;
   void Enable() override;
   void SelectOutputMode() override;
   void SelectInputMode() override;
   void SelectMode(Moder moder);
};