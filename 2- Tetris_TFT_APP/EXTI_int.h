/*
 * EXTI_int.h
 *
 *  Created on: Sep 4, 2020
 *      Author: eslam
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_






void MEXTI_vidInit(u8 Copy_Mode ,u8 Copy_Line);

void MEXTI_vidEnableEXTI(u8 Copy_u8Line);

void MEXTI_vidDisableEXTI(u8 Copy_u8Line);

void MEXTI_vidSwTrigger(u8 Copy_u8Line);

void MEXTI_vidSetCallBack(u8 Copy_u8Line , void(*ptr) (void) );



#define LINE_0      0
#define LINE_1      1
#define LINE_2      2
#define LINE_3      3
#define LINE_4      4
#define LINE_5      5
#define LINE_6      6
#define LINE_7      7
#define LINE_8      8
#define LINE_9      9
#define LINE_10     10
#define LINE_11     11
#define LINE_12     12
#define LINE_13     13
#define LINE_14     14
#define LINE_15     15




#define   RISING      0
#define   FALLING     1
#define   ONCHANGE    2




#endif /* EXTI_INT_H_ */
