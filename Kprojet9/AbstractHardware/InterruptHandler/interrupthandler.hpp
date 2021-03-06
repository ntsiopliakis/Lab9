//
// Created by Sergey on 21.11.2019.
//

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP

#include <array>
#include "tim2registers.hpp"  //for TIM2
#include "gpiocregisters.hpp"  //for TIM2
#include "ledsIndicator.h" 
#include "adc.h"
#include "Button.h"
#include "usart2registers.hpp"
#include "stdio.h"
#include "measurerconfig.h"
#include "usartconfig.h"
class InterruptHandler 
{
public:
  static void DummyHandler() 
  { 
    for(;;) 
    {
    } 
  }
  
  static void Usart2InterruptHandler()
  {
    static uint32_t RXit=0;
    static uint32_t TXit=0;
    static uint32_t lenRXmessage;
    static uint32_t lenTXmessage;
    static double sendValue;
    static char strTemp[50]="Temperature?";
    static char strVolt[50]="Voltage?";
    
    if(USART2::SR::RXNE::DataRecieved::IsSet())
    {
      RXbuff[RXit++]=USART2::DR::Get();
      if(RXbuff[RXit-1]=='\r')
      {
        RXbuff[RXit-1]='\0';
        RXit=0;
        if(!strcmp(strTemp,RXbuff))
        {
          sendValue=termometer.GetValue();
          if(!USART2::CR1::TE::Enable::IsSet())
          {
            sprintf(TXbuff,"Temperature: %3.4f  C\n",sendValue);
            
            lenTXmessage = std::strlen(TXbuff)+1;
            USART2::CR1::TE::Enable::Set();
            USART2::CR1::TXEIE::InterruptWhenTXE::Set();
            USART2::DR::Write(TXbuff[TXit++]);
          }
        }
        else
        {
          if(!strcmp(strVolt,RXbuff))
          {
            sendValue=potensiometer.GetValue();
            if(!USART2::CR1::TE::Enable::IsSet())
            {
              sprintf(TXbuff,"Voltage: %3.4f V\n",sendValue);
              lenTXmessage = std::strlen(TXbuff)+1;
              USART2::CR1::TE::Enable::Set();
              USART2::CR1::TXEIE::InterruptWhenTXE::Set();
              USART2::DR::Write(TXbuff[TXit++]);
            }
          }
          else return;
        }
      }
    }
    if(USART2::CR1::TE::Enable::IsSet()&&USART2::SR::TXE::DataRegisterEmpty::IsSet())
    {
      if(TXit==lenTXmessage)
      {
        TXit=0;
        USART2::CR1::TE::Disable::Set();
        USART2::CR1::TXEIE::InterruptInhibited::Set();
      }
      else
      {
        USART2::DR::Write(TXbuff[TXit++]);
      }
    }
  }
  
  
  static void TimerHandler()
  {
    ITimerInterrupted& timer=ledsIndicator.GetTimer();
    if (timer.IsOverFlowed())
    {      
      adc1.Start();
      uint16_t codeADU1=adc1.GetCode();
      uint16_t codeADU2=adc1.GetCode();
      termometer.AddValue(termometer.ConvertADU(codeADU1));
      potensiometer.AddValue(potensiometer.ConvertADU(codeADU2));
      
      if(flagIndicatorSwitch)
      {
        ledsIndicator.UpdateIndicator(termometer); 
      }
      else
      {
        ledsIndicator.UpdateIndicator(potensiometer);
      }
    }
  }
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
