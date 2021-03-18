/*************************************/
/* Author      : Eslam               */
/* Date        : 22 Aug 2020         */
/* Version     : V01                 */
/*************************************/

#ifndef NVIC_INT_H
#define NVIC_INT_H


void MNVIC_vidEnableInterrupt(u8 Copy_u8IntNumber);

void MNVIC_vidDisableInterrupt(u8 Copy_u8IntNumber);

void MNVIC_vidSetPendingFlag(u8 Copy_u8IntNumber);

void MNVIC_vidClrPendingFlag(u8 Copy_u8IntNumber);

u8 MNVIC_vidGetActiveFlag(u8 Copy_u8IntNumber);

void MNVIC_vidInit(void);
void MNVIC_vidSetPriority(u8 Copy_PeripheralIdx ,u8 Copy_u8IntProirity);

#endif 
