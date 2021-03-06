//#include <cstdint>            //for int types such as uint32_t
#include "gpioaregisters.hpp" //for Gpioa
#include "gpiocregisters.hpp" //for Gpioc
#include "gpiobregisters.hpp" //for Gpiob
#include "rccregisters.hpp"   //for RCC
#include "tim2registers.hpp"   //for SPI2
#include "nvicregisters.hpp"  //for NVIC
#include "ledsIndicator.h" 
#include "Button.h"
#include "led.h" 
#include "adc.h" 
#include "usart2registers.hpp"
#include "dma1registers.hpp"
using namespace std ;


constexpr uint32_t BaudRate=9600;
extern "C"
{
int __low_level_init(void)
{
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  
  RCC::APB1ENR::USART2EN::Enable::Set();
  GPIOA::MODER::MODER3::Alternate::Set();
  GPIOA::MODER::MODER2::Alternate::Set();
  GPIOA::AFRL::AFRL3::Af7::Set();
  GPIOA::AFRL::AFRL2::Af7::Set();
  GPIOA::PUPDR::PUPDR2::NoPullUpNoPullDown::Set();
  GPIOA::PUPDR::PUPDR3::PullUp::Set();
  USART2::CR1::OVER8::OversamplingBy16::Set();
  USART2::CR1::M::Data8bits::Set();
  USART2::CR2::STOP::OneStopBit::Set();
  USART2::CR1::PCE::ParityControlDisable::Set();
  //USART2::CR1::TE::Enable::Set();
  USART2::CR1::RE::Enable::Set();
  NVIC::ISER1::Write(1<<6);
  //USART2::CR1::TXEIE::InterruptWhenTXE::Set();
  USART2::CR1::RXNEIE::InterruptWhenRXNE::Set();
  uint32_t CLC = 16'000'000U;
  uint32_t USART_DIV = CLC/(BaudRate*8*(2 - USART2::CR1::OVER8::Get()));
  USART2::BRR::DIV_Mantissa::Set(USART_DIV);
  
  
  // RCC::AHB1ENR::DMA1EN::Enable::Set();
   
   
  
NVIC::ISER0::Write(1 << 28);
   return 1;
}
}

int main()
{
 adc1.Enable();
 adc1.Setting();
 adc1.CalibrateRefVoltage();
 ledsIndicator.Enable();

 

 
 USART2::CR1::UE::Enable::Set();
 
 
 ledsIndicator.Start();
 
  for(;;)    
  {
    if(button.WasPressed())
    {
      flagIndicatorSwitch=!flagIndicatorSwitch;
    }
  }
}

