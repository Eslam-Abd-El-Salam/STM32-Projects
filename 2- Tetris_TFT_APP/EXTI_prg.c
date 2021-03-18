/*
 * EXTI_prg.c
 *
 *  Created on: Sep 4, 2020
 *      Author: eslam
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXTI_int.h"
#include"EXTI_cfg.h"
#include"EXTI_priv.h"


static void (*EXTI_CallBack[15]) (void );

void MEXTI_vidInit(u8 Copy_Mode ,u8 Copy_Line)
{
	IMR->Byte = 0;
	if (Copy_Mode == RISING)        // Rising Mode
	{
		RTSR->Byte |= (1<<Copy_Line);
	}

	else if (Copy_Mode == FALLING)   // Falling Mode
	{
	FTSR->Byte |= (1<<Copy_Line);
	}

	else                     // On Change Mode
	{
		RTSR->Byte |= (1<<Copy_Line);      // Rising Mode
		FTSR->Byte |= (1<<Copy_Line);      // Falling Mode
	}



}



void MEXTI_vidEnableEXTI(u8 Copy_u8Line)
{

	if (Copy_u8Line <= 15)
	{
		IMR->Byte |= (1<<Copy_u8Line);     // Enable any Line user wants
	}

}




void MEXTI_vidDisableEXTI(u8 Copy_u8Line)
{


	if (Copy_u8Line <= 15)
	{
		IMR->Byte &=~ (1 << Copy_u8Line);    // Disable any Line user wants
	}

}



void MEXTI_vidSwTrigger(u8 Copy_u8Line)
{

	SWIER->Byte |= (1 << Copy_u8Line);
	PR->Byte &= ~ (1 << Copy_u8Line);

}



void MEXTI_vidSetCallBack(u8 Copy_u8Line , void(*ptr) (void) )
{
	for (u8 i=0; i<=15;i++)
	{
		if (Copy_u8Line == i)
		{
			EXTI_CallBack[i]=ptr;
		}
	}
}


void EXTI0_IRQHandler(void)
{
	EXTI_CallBack[0]();
	SET_BIT(PR->Byte,0);     // Clear Pending Bit

}

void EXTI1_IRQHandler(void)
{
	EXTI_CallBack[1]();
	SET_BIT(PR->Byte,1);     // Clear Pending Bit

}

void EXTI2_IRQHandler(void)
{
	EXTI_CallBack[2]();
	SET_BIT(PR->Byte,2);     // Clear Pending Bit

}

void EXTI3_IRQHandler(void)
{
	EXTI_CallBack[3]();
	SET_BIT(PR->Byte,3);     // Clear Pending Bit

}

void EXTI4_IRQHandler(void)
{
	EXTI_CallBack[4]();
	SET_BIT(PR->Byte,4);     // Clear Pending Bit

}

void EXTI5_IRQHandler(void)
{
	EXTI_CallBack[5]();
	SET_BIT(PR->Byte,5);     // Clear Pending Bit

}

void EXTI6_IRQHandler(void)
{
	EXTI_CallBack[6]();
	SET_BIT(PR->Byte,6);     // Clear Pending Bit

}

void EXTI7_IRQHandler(void)
{
	EXTI_CallBack[7]();
	SET_BIT(PR->Byte,7);     // Clear Pending Bit

}

void EXTI8_IRQHandler(void)
{
	EXTI_CallBack[8]();
	SET_BIT(PR->Byte,8);     // Clear Pending Bit

}

void EXTI9_IRQHandler(void)
{
	EXTI_CallBack[9]();
	SET_BIT(PR->Byte,9);     // Clear Pending Bit

}

void EXTI10_IRQHandler(void)
{
	EXTI_CallBack[10]();
	SET_BIT(PR->Byte,10);     // Clear Pending Bit

}

void EXTI11_IRQHandler(void)
{
	EXTI_CallBack[11]();
	SET_BIT(PR->Byte,11);     // Clear Pending Bit

}

void EXTI12_IRQHandler(void)
{
	EXTI_CallBack[12]();
	SET_BIT(PR->Byte,12);     // Clear Pending Bit

}

void EXTI13_IRQHandler(void)
{
	EXTI_CallBack[13]();
	SET_BIT(PR->Byte,13);     // Clear Pending Bit

}

void EXTI14_IRQHandler(void)
{
	EXTI_CallBack[14]();
	SET_BIT(PR->Byte,14);     // Clear Pending Bit

}

void EXTI15_IRQHandler(void)
{
	EXTI_CallBack[15]();
	SET_BIT(PR->Byte,15);     // Clear Pending Bit
}
