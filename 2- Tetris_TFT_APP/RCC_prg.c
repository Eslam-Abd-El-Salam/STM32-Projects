/************************************************************/
/* Author  : eslam                                          */
/* Version : V01                                            */ 
/* Date    : 8 Aug 2020                                     */
/************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"RCC_int.h"
#include"RCC_priv.h"
#include"RCC_cfg.h"



void RCC_vidEnableClock(u8 Copy_u8Bus, u8 Copy_u8PerId )
{
	if ( Copy_u8PerId <= 31 )
	{
		switch(Copy_u8Bus)
		{
			case AHB  : SET_BIT( RCC_AHBENR, Copy_u8PerId ); break;
			case APB1 : SET_BIT( RCC_APB1ENR, Copy_u8PerId ); break;
			case APB2 : SET_BIT( RCC_APB2ENR, Copy_u8PerId ); break;
			default   : /* Returen Error*/                   break;
		}
	}
	
	else
	{
		/* Return Error */
	}
	
	
	
	
	
}



void RCC_vidDisableClock(u8 Copy_u8Bus, u8 Copy_u8PerId )
{
	if ( Copy_u8PerId <= 31 )
	{
		switch(Copy_u8Bus)
		{
			case AHB  : CLR_BIT( RCC_AHBENR, Copy_u8PerId ); break;
			case APB1 : CLR_BIT( RCC_APB1ENR, Copy_u8PerId ); break;
			case APB2 : CLR_BIT( RCC_APB2ENR, Copy_u8PerId ); break;
			default   : /* Returen Error*/                   break;
		}
	}
	
	else
	{
		/* Return Error */
	}
	
	
	
	
	
}


void RCC_vidInitSysClock(void)

{
	
	#if     RCC_CLOCK_TYPE ==  RCC_HSE_CRYSTAL
	               
				    RCC_CR = 0x00010000;   /*Enable HSE Without bypass */
	                RCC_CFGR=0x00000001;  

	#elif   RCC_CLOCK_TYPE ==  RCC_HSE_RC
	
                    RCC_CR = 0x00050000;   /*Enable HSE With bypass */
	                RCC_CFGR=0x00000001;
					
	#elif   RCC_CLOCK_TYPE ==  RCC_HSI
	               
				    RCC_CR = 0x00000081;   /* Enable HSI + Trimming = 16 default value */
	                RCC_CFGR=0x00000000;
					
	#elif   RCC_CLOCK_TYPE ==  RCC_PLL
	
	    #if    RCC_PLL_INPUT == RCC_PLL_HSI_DIV_2

	                RCC_CFGR = ( (0x00000002) | (RCC_PLL_MUL_VAL << 18) );  /* Select Multiplication Value and HSI DIV by 2    */
	                RCC_CR   = 0x01000081;                                  /* Enable PLL and HSI + Trimming = 16 as default  */
		
		#elif  RCC_PLL_INPUT == RCC_PLL_HSE_DIV_2

	                RCC_CFGR = ( (0x00030002) | (RCC_PLL_MUL_VAL << 18) );  /* Select Multiplication Value and HSE DIV by 2 */
	                RCC_CR   = 0x01010000;                                  /* Enable PLL and HSE Crystal */

		#elif  RCC_PLL_INPUT == RCC_PLL_HSE

	                RCC_CFGR = ( (0x00010002) | (RCC_PLL_MUL_VAL << 18) );  /* Select Multiplication Value and HSE Not DIV */
	                RCC_CR   = 0x01010000;                                  /* Enable PLL and HSE Crystal  */

	
	#else
		  #error("you chosed Wrong Clock type ")
	  
	
	#endif
#endif
	
}

