/*
 * SPIMaster.h
 *
 * Created: 9/26/2015 9:38:29 PM
 *  Author: alaam
 */ 


#ifndef SPIMASTER_H_
#define SPIMASTER_H_

#include <inttypes.h>


void SPI_MasterInit (void);

uint8_t SPI_MasterTransmit (uint8_t);

u8 SPI_MasterReceive (void);


#endif /* SPIMASTER_H_ */