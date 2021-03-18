/*
 * SysTick_priv.h
 *
 *  Created on: Aug 29, 2020
 *      Author: eslam
 */

#ifndef SYSTICK_PRIV_H_
#define SYSTICK_PRIV_H_


#define STK_CTRL    *((volatile u32*)0xE000E010)
#define STK_LOAD    *((volatile u32*)0xE000E014)
#define STK_VAL     *((volatile u32*)0xE000E018)

#define CLK_SORCE_AHB                0
#define CLK_SORCE_AHB_DIV_8          1


#define     MSTK_SINGLE_INTERVAL    0
#define     MSTK_PERIOD_INTERVAL    1




#endif /* SYSTICK_PRIV_H_ */
