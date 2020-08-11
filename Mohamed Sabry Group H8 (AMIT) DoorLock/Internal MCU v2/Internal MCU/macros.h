/*
 * macros.h
 *
 * Created: 10/3/2015 10:43:10 AM
 *  Author: alaa
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define BV(bit)				(1<<bit)

#define SET_BIT(reg,bit)		reg |= BV(bit)

#define CLEAR_BIT(reg,bit)	reg &= ~BV(bit)

#define READ_BIT(reg, bit)	(reg&BV(bit))

#endif /* MACROS_H_ */