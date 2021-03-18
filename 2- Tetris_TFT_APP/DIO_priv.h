/*
 * DIO_priv.h
 *
 *  Created on: Aug 15, 2020
 *      Author: eslam
 */

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_


/* Register Addresses For Port A */
#define GPIOA_CRL *((u32*)(0x40010800 + 0x00))
#define GPIOA_CRH *((u32*)(0x40010800 + 0x04))
#define GPIOA_IDR *((u32*)(0x40010800 + 0x08))
#define GPIOA_ODR *((u32*)(0x40010800 + 0x0C))
#define GPIOA_BSR *((u32*)(0x40010800 + 0x10))
#define GPIOA_BRR *((u32*)(0x40010800 + 0x14))
#define GPIOA_LCK *((u32*)(0x40010800 + 0x18))

/* Register Addresses For Port B */
#define GPIOB_CRL *((u32*)(0x40010C00+0x00))
#define GPIOB_CRH *((u32*)(0x40010C00+0x04))
#define GPIOB_IDR *((u32*)(0x40010C00+0x08))
#define GPIOB_ODR *((u32*)(0x40010C00+0x0C))
#define GPIOB_BSR *((u32*)(0x40010C00+0x10))
#define GPIOB_BRR *((u32*)(0x40010C00+0x14))
#define GPIOB_LCK *((u32*)(0x40010C00+0x18))


/* Register Addresses For Port C */
#define GPIOC_CRL *((u32*)(0x40011000+0x00))
#define GPIOC_CRH *((u32*)(0x40011000+0x04))
#define GPIOC_IDR *((u32*)(0x40011000+0x08))
#define GPIOC_ODR *((u32*)(0x40011000+0x0C))
#define GPIOC_BSR *((u32*)(0x40011000+0x10))
#define GPIOC_BRR *((u32*)(0x40011000+0x14))
#define GPIOC_LCK *((u32*)(0x40011000+0x18))



#endif /* DIO_PRIV_H_ */
