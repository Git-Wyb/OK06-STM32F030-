#ifndef __M24C16_H__
#define __M24C16_H__

#include "IIC.h"


void Init_M24C16(void);
u1 M24C16_ReadOneByte(u2 ReadAddr);
void M24C16_WriteOneByte(u2 WriteAddr,u1 DataToWrite);
void AT24CXX_WriteLenByte(u2 WriteAddr,u4 DataToWrite,u1 Len);
u4 M24C16_ReadLenByte(u2 ReadAddr,u1 Len);
void M24C16_Read(u2 ReadAddr,u1 *pBuffer,u2 NumToRead);
void M24C16_Write(u2 WriteAddr,u1 *pBuffer,u2 NumToWrite);



#endif

