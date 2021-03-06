#pragma once


inline uint16_t UrefADU_Default = *reinterpret_cast<uint16_t*>(0x1FFF7A2A);
inline uint16_t TempCAL1=*reinterpret_cast<uint16_t*>(0x1FFF7A2C);
inline uint16_t TempCAL2=*reinterpret_cast<uint16_t*>(0x1FFF7A2E);

inline double Temp_k =(110.0-30.0)/(TempCAL2-TempCAL1);
inline double Temp_b =30.0-(110.0-30.0)/(TempCAL2-TempCAL1)*TempCAL1;
