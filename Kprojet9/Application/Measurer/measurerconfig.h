#pragma once
#include "measurer.h"

inline Potensiometer potensiometer(1, dynamic_cast<ADCdescriptor&>(adc1));
inline  Termometer termometer(23,27,1, dynamic_cast<ADCdescriptor&>(adc1));