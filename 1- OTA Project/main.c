/*
 * main.c
 *
 *  Created on: Oct 13, 2020
 *      Author: eslam
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"
#include "FPEC_interface.h"
#include"ESP_int.h"

void Parser_voidParseRecord(u8* Copy_u8BufData);
u8 glaf=0;
volatile u8  u8RecCounter     = 0;
volatile u16 u16TimerCounter  = 0;
volatile u8  u8BLWriteReq     = 1;
volatile u8  record_value     = 0;
volatile u8 *ptr_array        = 0;
volatile u8 flag              = 0;
volatile u8 Interruption_Flag = 0;
typedef void (*Function_t)(void);

Function_t addr_to_call = 0;
u8 x=0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);

	addr_to_call();
}


void checkInterruption(void){


	Interruption_Flag=1;

	if((ptr_array[8]=='1')|(ptr_array[8]=='\0')){

		MSTK_voidStopInterval();
		func();

	}
	else
	{

	}


}


void main(void)
{
	u8 Local_u8RecStatus;

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,14); /* USART1 */
	RCC_voidEnableClock(RCC_APB2,2);  /* PortA  */
	RCC_voidEnableClock(RCC_AHB,4);   /* FPEC   */
	MGPIO_VidSetPinDirection(GPIOA,9,0b1010);   /* TX AFPP */
	MGPIO_VidSetPinDirection(GPIOA,10,0b0100);  /* RC Input Floating */

	MUSART1_voidInit();
	MSTK_voidInit();
	MSTK_voidSetIntervalSingle(15000000,func);
	ESP_vidInit();
	ESP_vidConnectWifi((u8 *)"NoOne",(u8 *)"0181536158Eslam");

	MSTK_voidStopInterval();



	while(1)
	{



		ESP_vidConnectServer_Tcp((u8 *)"205.144.171.99",(u8 *)"80" );  // connect to server
		ESP_SendDatatoServer( (u8 *)"eslamm-001-site1.btempurl.com/script.php?Status_1=k",(u8 *)"64"  );  // send first record then  Remove it (Record) and shifting up The other Record Or line

		Try_Get_Data_Again:
		MSTK_voidSetIntervalSingle(15000000,checkInterruption);
		ESP_vidConnectServer_Tcp((u8 *)"205.144.171.99",(u8 *)"80" );  // connect to server

		record_value= (ESP_u8ReceiveHttpReq( (u8 *)"eslamm-001-site1.btempurl.com", (u8 *)"53")); // Read First Line(Record) From extraction file and send it to parser

		ptr_array = Record() ;

		if (record_value == 1)

		{
			MSTK_voidStopInterval();

			if (u8BLWriteReq == 1)
			{
				FPEC_voidEraseAppArea();
				u8BLWriteReq = 0;
			}

			/* Parse */
			Parser_voidParseRecord(ptr_array);
			u8RecCounter = 0;

		}

		else
		{
			if((ptr_array[8]=='1')|(ptr_array[8]=='\0'))
				MSTK_voidStopInterval();
			func();

		}

		if (Interruption_Flag == 1)
		{
			Interruption_Flag=0;
			goto Try_Get_Data_Again;

		}
	}



}
