/************************************************************/
/* Author  : eslam                                          */
/* Version : V01                                            */ 
/* Date    : 8 Aug 2020                                     */

#ifndef  _RCC_CFG_H
#define  RCC_CFG_H


/*** System Clock Type ******/

#define   RCC_u8_HSI           1
#define   RCC_u8_HSE           2
#define   RCC_u8_PLL           3
#define   RCC_u8_NOTALLOWED    4


/*********************************************
    **** System Clock Switch ****
  *  Choose one of The Following :              
  *  RCC_u8_HSI                                 
  *  RCC_u8_HSE                             
  *  RCC_u8_PLL                                 
  *  RCC_u8_NotAllowed                              
  *******************************************/

#define  RCC_CLOCK_TYPE     RCC_HSE_CRYSTAL
 
 

/***************************************************
 *  option :
 *  RCC_PLL_IN_HSI_DIV_2
 *  RCC_PLL_IN_HSE_DIV_2
 *  RCC_PLL_IN_HSE
 
*****************************************************/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT   RCC_PLL_IN_HSE_DIV_2
#endif



/*  Options   2  to  16    */
/**********************************
*PLL_INPUT_CLOCK_X2
*PLL_INPUT_CLOCK_X3
*PLL_INPUT_CLOCK_X4
*PLL_INPUT_CLOCK_X5
*PLL_INPUT_CLOCK_X6
*PLL_INPUT_CLOCK_X7
*PLL_INPUT_CLOCK_X8
*PLL_INPUT_CLOCK_X9
*PLL_INPUT_CLOCK_X10
*PLL_INPUT_CLOCK_X11
*PLL_INPUT_CLOCK_X12
*PLL_INPUT_CLOCK_X13
*PLL_INPUT_CLOCK_X14
*PLL_INPUT_CLOCK_X15
*PLL_INPUT_CLOCK_X16
*PLL_INPUT_CLOCK_X16
***********************************/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL   PLL_INPUT_CLOCK_X2
#endif






#endif
