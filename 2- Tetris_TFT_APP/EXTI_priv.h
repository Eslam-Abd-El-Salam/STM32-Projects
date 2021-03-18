/*
 * EXTI_priv.h
 *
 *  Created on: Sep 4, 2020
 *      Author: eslam
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_


typedef union{



	struct {

		volatile u16 Bit0:1  ;
		volatile u16 Bit1:1  ;
		volatile u16 Bit2:1  ;
		volatile u16 Bit3:1  ;
		volatile u16 Bit4:1  ;
		volatile u16 Bit5:1  ;
		volatile u16 Bit6:1  ;
		volatile u16 Bit7:1  ;
		volatile u16 Bit8:1  ;
		volatile u16 Bit9:1  ;
		volatile u16 Bit10:1 ;
		volatile u16 Bit11:1 ;
		volatile u16 Bit12:1 ;
		volatile u16 Bit13:1 ;
		volatile u16 Bit14:1 ;
		volatile u16 Bit15:1 ;


	}Bit;

	 u16 Byte;

}EXTI_t;

#define IMR     ((volatile EXTI_t*)0x40010400)
#define EMR     ((volatile EXTI_t*)0x40010404)
#define RTSR    ((volatile EXTI_t*)0x40010408)
#define FTSR    ((volatile EXTI_t*)0x4001040c)
#define SWIER   ((volatile EXTI_t*)0x40010410)
#define PR      ((volatile EXTI_t*)0x40010414)










#endif /* EXTI_PRIV_H_ */
