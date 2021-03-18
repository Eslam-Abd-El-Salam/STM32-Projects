/************************************************************/
/* Author  : eslam                                          */
/* Version : V01                                            */ 
/* Date    : 8 Aug 2020                                     */

#ifndef _RCC_INT_H
#define RCC_INT_H

#define  AHB    0
#define  APB1   1
#define  APB2   2



void RCC_vidEnableClock(u8 Copy_u8Bus, u8 Copy_u8PerId );
void RCC_vidDisableClock(u8 Copy_u8Bus, u8 Copy_u8PerId );
void RCC_vidInitSysClock(void);

#endif
