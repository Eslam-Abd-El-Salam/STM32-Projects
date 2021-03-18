/*
 * DIO_prg.c
 *
 *  Created on: Aug 15, 2020
 *      Author: eslam
 */

#include"STD_Types.h"
#include"BIT_MATH.h"
#include"DIO_int.h"
#include"DIO_priv.h"


void GPIO_vidSetPinDir(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Mode)
{

	switch(Copy_u8Port)
	{
	case GPIOA:

		if (Copy_u8Pin <= 7 )
		{
			GPIOA_CRL &= ~  ((0b1111)<<(Copy_u8Pin*4));
			GPIOA_CRL |=   ((Copy_u8Mode) << (Copy_u8Pin*4));

		}

		else if (Copy_u8Pin <= 15 )
		{

			GPIOA_CRH &= ~ ((0b1111)<<((Copy_u8Pin - 8)*4)) ;
			GPIOA_CRH |=   ((Copy_u8Mode) << ((Copy_u8Pin-8)*4))	;

		}
		break;

	case GPIOB:


		if (Copy_u8Pin <= 7 )
		{
			GPIOB_CRL &= ~ ((0b1111)<<(Copy_u8Pin*4)) ;
			GPIOB_CRL |=   ((Copy_u8Mode) << (Copy_u8Pin*4))	;

		}

		else if (Copy_u8Pin <= 15 )
		{

			GPIOB_CRH &= ~ ((0b1111)<<((Copy_u8Pin-8)*4)) ;
			GPIOB_CRH |=   ((Copy_u8Mode) << ((Copy_u8Pin - 8)*4))	;

		}


		break;

	case GPIOC:

		if (Copy_u8Pin <= 7 )
		{
			GPIOC_CRL &= ~ ((0b1111)<<(Copy_u8Pin*4)) ;
			GPIOC_CRL |=   ((Copy_u8Mode) << (Copy_u8Pin*4))	;

		}

		else if (Copy_u8Pin <= 15 )
		{

			GPIOC_CRH &= ~ ((0b1111)<<((Copy_u8Pin - 8 )*4)) ;
			GPIOC_CRH |=  ( (Copy_u8Mode) << ((Copy_u8Pin - 8)*4))	;

		}

		break;







	}


}


void GPIO_vidSetPinVal(u8 Copy_u8Port ,u8 Copy_u8Pin, u8 Copy_u8Val)
{


	switch(Copy_u8Port)
	{
	case GPIOA:

		if (Copy_u8Val == GPIO_HIGH )
		{
			//SET_BIT(GPIOA_ODR,Copy_u8Pin);
			GPIOA_BSR =(1<<Copy_u8Pin);

		}

		else if (Copy_u8Val == GPIO_LOW )
		{

			//CLR_BIT(GPIOA_ODR,Copy_u8Pin);
			GPIOA_BRR = (1<<Copy_u8Pin);

		}
		break;

	case GPIOB:


		if (Copy_u8Val == GPIO_HIGH )
		{
			//SET_BIT(GPIOB_ODR,Copy_u8Pin);
			GPIOB_BSR =(1<<Copy_u8Pin);
		}

		else if (Copy_u8Val == GPIO_LOW )
		{

			//CLR_BIT(GPIOB_ODR,Copy_u8Pin);
			GPIOB_BRR = (1<<Copy_u8Pin);
		}


		break;

	case GPIOC:

		if (Copy_u8Val == GPIO_HIGH )
		{
			//SET_BIT(GPIOC_ODR,Copy_u8Pin);
			GPIOC_BSR =(1<<Copy_u8Pin);
		}

		else if (Copy_u8Val == GPIO_LOW )
		{

			//CLR_BIT(GPIOC_ODR,Copy_u8Pin);
			GPIOC_BRR = (1<<Copy_u8Pin);

		}
		break;





	}




}


u8 GPIO_vidGetPinVal(u8 Copy_u8Port ,u8 Copy_u8Pin)
{

	u8 LOC_Result = 0 ;

	switch(Copy_u8Port)
	{
	case GPIOA:

		LOC_Result = GET_BIT(GPIOA_IDR,Copy_u8Pin);

		break;

	case GPIOB:

		LOC_Result = GET_BIT(GPIOB_IDR,Copy_u8Pin);

		break;

	case GPIOC:

		LOC_Result = GET_BIT(GPIOC_IDR,Copy_u8Pin);

		break;

	default:   break;

	}
	return LOC_Result ;

}
