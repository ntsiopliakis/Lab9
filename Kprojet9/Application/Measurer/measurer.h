#pragma once
#include "adc.h"
#include "Calibration.h"

class DispObject
{
public:
  virtual double GetMinValue()=0;
  virtual double GetMaxValue()=0;
  virtual double GetValue()=0;
};
class Measurer: public DispObject
{
protected:
  double* pValue;
  uint32_t buffLength;
  ADCdescriptor& adc;
  uint32_t iterator=0;
public:
  double minVal;
  double maxVal;
  virtual double ConvertADU( uint16_t val)=0;
  double* GetValuePointer()
  {
    return pValue;
  }
  
  double GetValue(uint32_t i)
  {
    return pValue[i];
  }
  double GetValue()
  {
    return pValue[iterator];
  }
  double GetMinValue()
  {
    return minVal;
  }
  double GetMaxValue()
  {
    return maxVal;
  }
  uint32_t GetBuffLength()
  {
    return buffLength;
  }
  void AddValue(double val)
  {
    iterator=(iterator<buffLength)?(iterator+1):0;
    pValue[iterator]=val;
  }
  
  Measurer(double minVal, double maxVal, uint32_t buffLength, ADCdescriptor& adc): minVal(minVal),maxVal(maxVal),buffLength(buffLength), adc(adc)
  {
    pValue = new double[buffLength];
  }
  virtual ~Measurer()
  {
    delete[] pValue;
  }
};

class Potensiometer : public Measurer
{
public:
  Potensiometer(double minVal, double maxVal, uint32_t buffLength, ADCdescriptor& adc):Measurer(minVal, maxVal, buffLength, adc)
  {
  }
  Potensiometer( uint32_t buffLength, ADCdescriptor& adc):Measurer( 0, adc.GetRefVoltage(), buffLength, adc)
  {
  }  
  double ConvertADU(uint16_t ADU) override
  {
    return (adc.GetRefVoltage()/adc.GetNumOfBits())*ADU;
  }
  
  ~Potensiometer()
  {
  }
};

class Termometer : public Measurer
{
public:
  Termometer(double minVal, double maxVal, uint32_t buffLength, ADCdescriptor& adc):Measurer(minVal, maxVal, buffLength, adc)
  {
  }
  
  double ConvertADU(uint16_t ADU) override
  {
    return Temp_k*ADU + Temp_b;
  }
  
  ~Termometer()
  {
  }
  
};



