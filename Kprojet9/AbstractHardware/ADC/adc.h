#pragma once
#include <cstdint> // for uint8_t
#include "gpiocregisters.hpp" // for GPIOC
#include "gpioaregisters.hpp" // for GPIOC
#include "adc1registers.hpp"
#include "rccregisters.hpp"   //for RCC
#include "adccommonregisters.hpp"

class ADCdescriptor
{
public:
  double virtual GetRefVoltage()=0;
  uint32_t virtual GetNumOfBits()=0;
};


class IADC: public ADCdescriptor
{
public: 
   void virtual Enable() = 0;
   void virtual Setting()=0;
   void virtual Start() = 0;
   bool virtual IsCovertionCompleted()=0;
   void virtual Stop() = 0;
   double virtual GetVoltage() = 0;
   uint16_t virtual Get() = 0;
   uint16_t virtual GetCode() = 0;
   double virtual GetRefVoltage()=0;
   double virtual CalibrateRefVoltage()=0;
   uint32_t virtual GetNumOfBits()=0;
   
};



template<typename PortType>
struct APB2ENR_of
{
};
template<>
struct APB2ENR_of<ADC1>
{
  using Enable = RCC::APB2ENR::ADC1EN::Enable;
  using Disable = RCC::APB2ENR::ADC1EN::Disable;
};

template<typename ADCx>
class ADC: public IADC
{
  uint32_t numOfBits=4096;
  double voltageRef=3.3;
public:
  
  void Enable() override
  {
    APB2ENR_of<ADCx>::Enable::Set();
  }
  void Setting() override
  {
    // User Code 
    ADCx::CR1::RES::Bits12::Set();
    ADCx::CR1::SCAN::Enable::Set();
    ADCx::CR2::CONT::SingleConversion::Set();
    ADCx::CR2::EOCS::EachConversion::Set();
    ADCx::SQR1::L::Conversions2::Set();
    ADCx::SQR3::SQ1::Channel16::Set();
    ADCx::SQR3::SQ2::Channel0::Set();
    ADCx::SMPR2::SMP0::Cycles480::Set();
    ADCx::SMPR2::SMP1::Cycles480::Set();    
    ADC_Common::CCR::TSVREFE::Enable::Set();
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();
    ADCx::CR2::ADON::Enable::Set();
  }
  
   void Start() override
   {
     ADCx::CR2::SWSTART::On::Set();
   }
   bool IsCovertionCompleted() override
   {
     return ADCx::SR::EOC::ConversionComplete::IsSet();
   }
   void Stop() override
   {
     ADCx::CR2::ADON::Disable::Set();
   }
   double GetVoltage() override
   {
    while(!ADCx::SR::EOC::ConversionComplete::IsSet())
    {
    }
    return voltageRef/numOfBits*ADCx::DR::Get();
   }
  uint16_t Get() override
  {
    return ADCx::DR::Get();
  }
  
  uint16_t GetCode() override
  {
    while(!ADCx::SR::EOC::ConversionComplete::IsSet())
    {
    }
    return ADCx::DR::Get();
  }
  double GetRefVoltage() override
  {
    return voltageRef;
  }
  
  uint32_t GetNumOfBits() override
  {
    return numOfBits;
  }
  double CalibrateRefVoltage() override
  {
    ADCx::CR2::ADON::Disable::Set();
    auto currentChannel=ADCx::SQR3::SQ1::Get();
    ADCx::SQR3::SQ1::Channel17::Set();
    ADCx::CR2::ADON::Enable::Set();
    ADCx::CR2::SWSTART::On::Set();
    while(!ADCx::SR::EOC::ConversionComplete::IsSet())
    {
    }
    uint16_t VrefADU = ADCx::DR::Get();
    ADCx::CR2::ADON::Disable::Set();
    ADCx::SQR3::SQ1::Set(currentChannel);
    ADCx::CR2::ADON::Enable::Set();
    uint16_t VrefADU_default = *reinterpret_cast<uint16_t*>(0x1FFF7A2A);
    voltageRef = 3.3*VrefADU_default/VrefADU;
    return voltageRef;
  }
  
};

inline ADC<ADC1> adc1;