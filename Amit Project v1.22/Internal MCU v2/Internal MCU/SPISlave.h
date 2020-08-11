/*
 * SPISlave.h
 *
 * Created: 9/26/2015 10:19:49 PM
 *  Author: alaam
 */ 


#ifndef SPISLAVE_H_
#define SPISLAVE_H_

#include "STDTypes.h"

void SPI_SlaveInit (void);

u8 SPI_SlaveReceive (u8);

void SPI_SlaveTransmit(u8);



#endif /* SPISLAVE_H_ */