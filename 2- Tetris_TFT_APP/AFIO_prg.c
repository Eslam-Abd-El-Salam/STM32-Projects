/*
 * AFIO_prg.c
 *
 *  Created on: Sep 4, 2020
 *      Author: eslam
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"AFIO_int.h"
#include"AFIO_cfg.h"
#include"AFIO_priv.h"





void MAFIO_vidSetEXTICfg(u8 Copy_u8Line ,u8 Copy_u8Port_Map )
{

	u8 Local_u8RegIndex = 0;

	if(Copy_u8Line <= 3)
	{
		Local_u8RegIndex = 0;
	}
	else if (Copy_u8Line <= 7)
	{
		Local_u8RegIndex=1;
		Copy_u8Line -=4 ;
	}



	else if (Copy_u8Line <= 11)
	{
		Local_u8RegIndex=2;
		Copy_u8Line -=8 ;
	}


	else if (Copy_u8Line <= 15)
	{
		Local_u8RegIndex=3;
		Copy_u8Line -=12 ;
	}

	AFIO->EXTICR[Local_u8RegIndex]   &= ~((0b1111)<<(Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex]   |=  ((Copy_u8Port_Map)<<(Copy_u8Line * 4));
}





void MAFIO_vidSetSPICfg(u8 Copy_u8Port_Map )
{

	if (Copy_u8Port_Map == AIF_PORTA)
	{
		AFIO->MAPR &= 0xFFFE;
	}


	else
	{
		AFIO->MAPR |=0x1 ;
	}


}

