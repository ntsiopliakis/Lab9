#pragma once
#include <cstdint> // for uint8_t
#include "gpiocregisters.hpp" // for GPIOC
#include "gpioaregisters.hpp" // for GPIOC
#include "tim2registers.hpp" 
#include "tim3registers.hpp" 
#include "tim4registers.hpp" 
#include "tim5registers.hpp" 
#include "rccregisters.hpp"   //for RCC


template<typename TIMx>
struct APB1ENR_of
{
};
template<>
struct APB1ENR_of<TIM2>
{
  using Enable= RCC::APB1ENR::TIM2EN::Enable;
  using Disable= RCC::APB1ENR::TIM2EN::Disable;
};
template<>
struct APB1ENR_of<TIM3>
{
  using Enable= RCC::APB1ENR::TIM3EN::Enable;
  using Disable= RCC::APB1ENR::TIM3EN::Disable;
};
template<>
struct APB1ENR_of<TIM4>
{
  using Enable= RCC::APB1ENR::TIM4EN::Enable;
  using Disable= RCC::APB1ENR::TIM4EN::Disable;
};
template<>
struct APB1ENR_of<TIM5>
{
  using Enable= RCC::APB1ENR::TIM5EN::Enable;
  using Disable= RCC::APB1ENR::TIM5EN::Disable;
};


class ITimerInterrupted
{
  public: 
   bool virtual IsOverFlowed()=0;

};

class ITimer: public ITimerInterrupted
{
public: 
   void virtual Enable() = 0;
   void virtual SetPeriod(uint32_t num) = 0;
   void virtual Start() = 0;
   void virtual Stop() = 0;
   bool virtual IsOverFlowed()=0;
};



template<typename TIMx, uint32_t inputFreq>
class Timer: public ITimer
{

  void Enable() override
  {
    APB1ENR_of<TIMx>::Enable::Set();
    TIMx::CR1::URS::OverflowEvent::Set();
    TIMx::ARR::Write(50-1) ;
    TIMx::PSC::Write(inputFreq/1000-1U);
   TIMx::DIER::UIE::Enable::Set() ;
   TIM2::SR::UIF::NoInterruptPending::Set();
   TIMx::CNT::Write(0);    
  }
  void SetPeriod(uint32_t period) override
  {
    TIMx::ARR::Write(period-1U);
    TIMx::CNT::Write(0);
    TIMx::SR::UIF::NoInterruptPending::Set();
  }
  void Start() override
  {
    TIM2::CR1::CEN::Enable::Set();
  }
    void Stop() override
  {
    TIM2::CR1::CEN::Disable::Set();
  }
  bool IsOverFlowed() override
  {
    bool b=TIMx::SR::UIF::InterruptPending::IsSet() && TIMx::DIER::UIE::Enable::IsSet();
    if(b)
    {
      TIM2::SR::UIF::NoInterruptPending::Set();
    }
    return b;
  }
};