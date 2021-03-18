/*
 * SysTick_int.h
 *
 *  Created on: Aug 29, 2020
 *      Author: eslam
 */

#ifndef SYSTICK_INT_H_
#define SYSTICK_INT_H_

void MSTK_vidInit(void);
void MSTK_vidSetBusyWait(u32 Copy_u8Ticks);
void MSTK_vidSetIntervalSingle (u32 Copy_u8Ticks , void (*Copy_ptr)(void));
void MSTK_vidSetIntervalPeriodic(u32 Copy_u8Ticks , void (*Copy_ptr)(void));
void MSTK_vidStopTimer(void);
u32 MSTK_u32ElapsedTime(void);
u32 MSTK_u32GetRemainingTime(void);


#endif /* SYSTICK_INT_H_ */
