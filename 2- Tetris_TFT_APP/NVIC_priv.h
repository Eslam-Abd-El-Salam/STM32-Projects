/*************************************/
/* Author      : Eslam               */
/* Date        : 22 Aug 2020         */
/* Version     : V01                 */
/*************************************/

#ifndef NVIC_PRIV_H
#define NVIC_PRIV_H

/* Base Address   */

#define NVIC_ISER0    *((u32*)0xE000E100)    /* Enable External Interrupts from 0 to 31  */   
#define NVIC_ISER1    *((u32*)0xE000E104)    /* Enable External Interrupts from 32 to 63 */
 
#define NVIC_ICER0    *((u32*)0xE000E180)    /* Disable External Interrupts from 32 to 63 */ 
#define NVIC_ICER1    *((u32*)0xE000E184)    /* Disable External Interrupts from 32 to 63 */ 

#define NVIC_ISPR0     *((u32*)0xE000E200)    /* Enable Pending External Interrupts from 0 to 31 */ 
#define NVIC_ISPR1     *((u32*)0xE000E204)    /* Enable Pending External Interrupts from 32 to 63 */

#define NVIC_ICPR0     *((u32*)0xE000E280)    /* Disable Pending External Interrupts from 0 to 31 */ 
#define NVIC_ICPR1     *((u32*)0xE000E284)    /* Disable Pending External Interrupts from 32 to 63 */

#define NVIC_IABR0	   *((volatile u32*)0xE000E300)
#define NVIC_IABR1	   *((volatile u32*)0xE000E304)



#define NVIC_IPR       ((u8*)0xE000E400)


#define MNVIC_GROUP_4_SUB_0     0x05FA0300
#define MNVIC_GROUP_3_SUB_1     0x05FA0400
#define MNVIC_GROUP_2_SUB_2     0x05FA0500
#define MNVIC_GROUP_1_SUB_3     0x05FA0600
#define MNVIC_GROUP_0_SUB_4     0x05FA0700

#endif
