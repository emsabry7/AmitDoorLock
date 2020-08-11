/*
 * i2c.h
 *
 * Created: 10/19/2015 10:33:52 PM
 *  Author: alaa
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <inttypes.h>

void I2c_Init (void);

int8_t I2c_Send1 (uint8_t data);

uint8_t I2c_Recv1 (void);




#endif /* I2C_H_ */