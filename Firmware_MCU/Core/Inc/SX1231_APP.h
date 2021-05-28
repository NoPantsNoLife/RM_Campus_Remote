#ifndef __SX1231_APP_H__
#define __SX1231_APP_H__

#include "SX1231_Driver.h"
#include "main.h"

extern SX1231_Typedef SX1231_Primary;

#define SX1231_PayloadLength 0x30


void SX1231_Init_Primary();
uint8_t Checksum(uint8_t bfr[], uint32_t length);
void SX1231_Primary_TransmitPacket(uint8_t bfr[SX1231_PayloadLength]);
void SX1231_Primary_Reset();


#endif