/*
 * SysTick_prg.c
 *
 *  Created on: Aug 29, 2020
 *      Author: eslam
 */

#include"STD_Types.h"
#include"BIT_MATH.h"
#include"SysTick_priv.h"
#include"SysTick_cfg.h"
#include"SysTick_int.h"

void (*Callback) (void);

static u8 MSTK_u8ModeOfInterval;

void MSTK_vidInit(void)
{

#if CLOCK_SOURCE  ==  CLK_SORCE_AHB_DIV_8

	STK_CTRL = 0x00000000;

#elif CLOCK_SOURCE ==  CLK_SORCE_AHB

	STK_CTRL = 0x00000004;

#endif

}



void MSTK_vidSetBusyWait(u32 Copy_u8Ticks)
{

	STK_LOAD =  Copy_u8Ticks ;  /* Load Value to be Counted */
	STK_CTRL |= 0x00000001;     /* Enable Timer */
	while (GET_BIT(STK_CTRL,16) == 0);
	/** Disable Timer **/
	STK_CTRL = 0x00000000;
	STK_LOAD = 0x000000;
	STK_VAL  = 0x000000;

}



void MSTK_vidSetIntervalSingle (u32 Copy_u8Ticks , void (*Copy_ptr)(void))
{
	STK_LOAD = Copy_u8Ticks;  /* Load value to be counted */
	STK_CTRL |= 0x00000003;   /* Enable Timer & Enable Interrupt */
	Callback = Copy_ptr;

	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL  ;

}



void MSTK_vidSetIntervalPeriodic(u32 Copy_u8Ticks , void (*Copy_ptr)(void))
{


	STK_LOAD = Copy_u8Ticks;  /* Load value to be counted */
	STK_CTRL |= 0x00000003;   /* Enable Timer & Enable Interrupt */
	Callback = Copy_ptr;

	/* Set Mode to Periodic */
		MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;


}



void MSTK_vidStopTimer(void)
{

	STK_CTRL = 0x00000000;
	STK_LOAD = 0x000000;
	STK_VAL  = 0x000000;

}



u32 MSTK_u32ElapsedTime(void)
{
	u32 Load_value =  STK_LOAD;
	u32 Elapsed_time = Load_value - MSTK_u32GetRemainingTime();

	return Elapsed_time;
}



u32 MSTK_u32GetRemainingTime(void)
{
	u32 Remaining_Time = STK_VAL;
	return Remaining_Time;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temporary;

	if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt and Timer */

		STK_CTRL = 0x00000000;
		STK_LOAD = 0x000000;
		STK_VAL  = 0x000000;

	}

	Callback();

	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(STK_CTRL,16);

}

