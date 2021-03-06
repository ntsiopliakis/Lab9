#pragma once
#include <cstdint> // for uint8_t
#include "gpiocregisters.hpp" // for GPIOC
#include "gpioaregisters.hpp" // for GPIOC
#include "rccregisters.hpp" 

enum Moder
{
  Input=0,
  Output=1,
  Alternate=2,
  Analog=3,
  
}; 

template<typename PortType>
struct AHB1ENR_of
{
};
template<>
struct AHB1ENR_of<GPIOC>
{
  using Enable = RCC::AHB1ENR::GPIOCEN::Enable;
  using Disable = RCC::AHB1ENR::GPIOCEN::Disable;
};
template<>
struct AHB1ENR_of<GPIOA>
{
  using Enable = RCC::AHB1ENR::GPIOAEN::Enable;
  using Disable = RCC::AHB1ENR::GPIOAEN::Disable;
};

class IPort
{
public: 
  void virtual Toggle(uint8_t num) = 0;
  void virtual Write(uint32_t value) = 0;
  void virtual Set(uint32_t value)=0;
  void virtual Reset(uint32_t value)=0;
  uint32_t virtual Get()=0;
  bool virtual IsSet(uint8_t num) = 0;
  void virtual ModeSet(uint8_t num, Moder moder)= 0;
  void virtual Enable()=0;
  void virtual Disable()=0;
  bool virtual IsEnable()=0;
};


template<typename Reg>
class Port: public IPort 
{
 public:  
  void Toggle(uint8_t num) override
  {
    Reg::ODR::Toggle(1U << num);
  }
  bool IsSet(uint8_t num) override
  {
    return (Reg::IDR::Get()&(1<<num))!=0;
  }
  uint32_t Get() override
  {
    return Reg::IDR::Get();
  }
  void Write(uint32_t value) override
  {
    Reg::ODR::Write(value);
  }
  void Set(uint32_t value) override
  {
    Reg::BSRR::Write(value);
  }
  void Reset(uint32_t value) override
  {
    Reg::BSRR::Write(value<<16);
  }
  void ModeSet(uint8_t num, Moder moder) override
  {
    auto value = Reg::MODER::Get();
    value &= ~(3U<<(num*2U));
    value |= moder<<(num*2U);
    Reg::MODER::Write(value);
  }
  void Enable() override
  {
    AHB1ENR_of<Reg>::Enable::Set();
  }
  void Disable() override
  {
    AHB1ENR_of<Reg>::Disable::Set();
  }
  bool IsEnable() override
  {
    return AHB1ENR_of<Reg>::Enable::IsSet();
  }
};



