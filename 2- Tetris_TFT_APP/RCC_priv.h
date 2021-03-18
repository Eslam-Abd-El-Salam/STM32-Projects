/************************************************************/
/* Author  : eslam                                          */
/* Version : V01                                            */ 
/* Date    : 8 Aug 2020                                     */

#ifndef _RCC_PRIV_H
#define RCC_PRIV_H


/* Register Definitions  */

#define RCC_CR        *((u32*)0x40021000)
#define RCC_CFGR      *((u32*)0x40021004)
#define RCC_CIR       *((u32*)0x40021008)
#define RCC_APB2RSTR  *((u32*)0x4002100c)
#define RCC_APB1RSTR  *((u32*)0x40021010)
#define RCC_AHBENR    *((u32*)0x40021014)
#define RCC_APB2ENR   *((u32*)0x40021018)
#define RCC_APB1ENR   *((u32*)0x4002101C)
#define RCC_BDCR      *((u32*)0x40021020)
#define RCC_CSR       *((u32*)0x40021024)



/*** System Clock Type ******/

#define   RCC_HSE_CRYSTAL      1
#define   RCC_HSE_RC           2
#define   RCC_HSI              3
#define   RCC_PLL              4


/*** PLL Options ***/

#define  RCC_PLL_IN_HSI_DIV_2   1
#define  RCC_PLL_IN_HSE_DIV_2   2
#define  RCC_PLL_IN_HSE         3


/* PLL multiplication Factor */

#define PLL_INPUT_CLOCK_X2       0b0000
#define PLL_INPUT_CLOCK_X3       0b0001
#define PLL_INPUT_CLOCK_X4       0b0010
#define PLL_INPUT_CLOCK_X5       0b0011
#define PLL_INPUT_CLOCK_X6       0b0100
#define PLL_INPUT_CLOCK_X7       0b0101
#define PLL_INPUT_CLOCK_X8       0b0110
#define PLL_INPUT_CLOCK_X9       0b0111
#define PLL_INPUT_CLOCK_X10      0b1000
#define PLL_INPUT_CLOCK_X11      0b1001
#define PLL_INPUT_CLOCK_X12      0b1010
#define PLL_INPUT_CLOCK_X13      0b1011
#define PLL_INPUT_CLOCK_X14      0b1100
#define PLL_INPUT_CLOCK_X15      0b1101
#define PLL_INPUT_CLOCK_X16      0b1110
#define PLL_INPUT_CLOCK_X16      0b1111



#endif
