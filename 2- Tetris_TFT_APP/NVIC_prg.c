/*************************************/
/* Author      : Eslam               */
/* Date        : 22 Aug 2020         */
/* Version     : V01                 */
/*************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"NVIC_int.h"
#include"NVIC_priv.h"
#include"NVIC_cfg.h"

void MNVIC_vidInit(void)
{
#define SCB_AIRCR   *((u32*)0xE000ED0C)
	SCB_AIRCR = MNVIC_GROUB_SUP_DISTRIBUTION ;
}




void MNVIC_vidSetPriority(u8 Copy_PeripheralIdx ,u8 Copy_u8IntProirity)
{

	if (Copy_PeripheralIdx < 60)
	{

         NVIC_IPR[Copy_PeripheralIdx] = Copy_u8IntProirity ;

	}

	else
	{
		/* Report Error */
	}

}

void MNVIC_vidEnableInterrupt(u8 Copy_u8IntNumber)
{

	if ( Copy_u8IntNumber <= 31 )
	{

		NVIC_ISER0 = (1 << Copy_u8IntNumber);

	}

	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber = Copy_u8IntNumber - 32 ;
		NVIC_ISER1 =  ( 1 << Copy_u8IntNumber );	
	}

	else
	{
		/* Return Error */
	}


}



void MNVIC_vidDisableInterrupt(u8 Copy_u8IntNumber)
{


	if ( Copy_u8IntNumber <= 31 )
	{

		NVIC_ICER0 = (1 << Copy_u8IntNumber);

	}

	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber = Copy_u8IntNumber - 32 ;
		NVIC_ICER1 =  ( 1 << Copy_u8IntNumber );	
	}

	else
	{
		/* Return Error */
	}

}




void MNVIC_vidSetPendingFlag(u8 Copy_u8IntNumber)
{


	if ( Copy_u8IntNumber <= 31 )
	{

		NVIC_ISPR0 = (1 << Copy_u8IntNumber);

	}

	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber = Copy_u8IntNumber - 32 ;
		NVIC_ISPR1 =  ( 1 << Copy_u8IntNumber );	
	}

	else
	{
		/* Return Error */
	}

}




void MNVIC_vidClrPendingFlag(u8 Copy_u8IntNumber)
{


	if ( Copy_u8IntNumber <= 31 )
	{

		NVIC_ICPR0 = (1 << Copy_u8IntNumber);

	}

	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber = Copy_u8IntNumber - 32 ;
		NVIC_ICPR1 =  ( 1 << Copy_u8IntNumber );	
	}

	else
	{
		/* Return Error */
	}

}



u8 MNVIC_vidGetActiveFlag(u8 Copy_u8IntNumber)
{
	u8 Local_Result;

	if ( Copy_u8IntNumber <= 31 )
	{

		Local_Result = GET_BIT(NVIC_IABR0,Copy_u8IntNumber);

	}

	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber = Copy_u8IntNumber - 32 ;
		Local_Result = GET_BIT(NVIC_IABR1,Copy_u8IntNumber);
	}

	else
	{
		/* Return Error */
	}

	return Local_Result;

}


