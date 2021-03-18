/*
 * AFIO_priv.h
 *
 *  Created on: Sep 4, 2020
 *      Author: eslam
 */

#ifndef AFIO_PRIV_H_
#define AFIO_PRIV_H_


typedef struct {


	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;


}AFIO_t;


#define  AFIO  ((volatile AFIO_t *) 0x40010000 )



#endif /* AFIO_PRIV_H_ */
