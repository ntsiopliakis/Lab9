#pragma once
#include "pin.h"         // for Pin
#include "portsconfig.h" // for PortC, PortA

inline Pin pinLed1(5, portA);
inline  Pin pinLed2(9, portC);
inline  Pin pinLed3(8, portC);
inline  Pin pinLed4(5, portC);

inline  Pin pinButton(13, portC);
