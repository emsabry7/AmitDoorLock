/*
 * DIO.h
 *
 * Created: 14-Oct-15 10:40:21 AM
 *  Author: m-hos
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "StdTypes.h"

#define PA 0x00
#define PB 0x01
#define PC 0x02
#define PD 0x03

void Dio_InitPortDirection(u8 PortName, u8 PortDirection, u8 PortMask);
void Dio_WritePort(u8 PortName, u8 PortData, u8 PortMask);
u8   Dio_ReadPort(u8 PortName, u8 PortMAsk);

#endif /* DIO_H_ */