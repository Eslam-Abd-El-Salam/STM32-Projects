/*
 * TFT_prg.c
 *
 *  Created on: Sep 21, 2020
 *      Author: eslam
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TFT_int.h"
#include"Dio_int.h"
#include"SPI_int.h"
#include"SysTick_int.h"
#include"TFT_priv.h"
#include"TFT_cfg.h"



void TFT_vidInit(void)
{

	GPIO_vidSetPinDir(TFT_RST_PIN,OUTPUT_SPEED_2MHZ_PP);   //For RST
	GPIO_vidSetPinDir(TFT_A0_PIN,OUTPUT_SPEED_2MHZ_PP);   //For A0
	MSTK_vidInit();
	SPI_vidInit();

	GPIO_vidSetPinVal(TFT_RST_PIN,GPIO_HIGH);
	MSTK_vidSetBusyWait(100);
	GPIO_vidSetPinVal(TFT_RST_PIN,GPIO_LOW);
	MSTK_vidSetBusyWait(1);
	GPIO_vidSetPinVal(TFT_RST_PIN,GPIO_HIGH);
	MSTK_vidSetBusyWait(100);
	GPIO_vidSetPinVal(TFT_RST_PIN,GPIO_LOW);
	MSTK_vidSetBusyWait(100);
	GPIO_vidSetPinVal(TFT_RST_PIN,GPIO_HIGH);
	MSTK_vidSetBusyWait(120000);

	/* Sleep Out	 */
	vidWriteCommand(0x11);
	MSTK_vidSetBusyWait(150000);

	/* Color Mode */

	vidWriteCommand(0x3A);
	vidWriteData(0x05);

	/* Display on */
	vidWriteCommand(0x29);



}



void TFT_vidDisplayImage(const u16* Copy_image )
{
	u16 Counter;
	/* Set X Address*/
	vidWriteCommand(0x2A);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(127);

	/* Set Y Address*/
	vidWriteCommand(0x2B);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(159);

	/* RAM Write */
	vidWriteCommand(0x2C);

	for (Counter = 0 ; Counter <20480 ; Counter++)
	{
		/* Write The High Byte */

		vidWriteData(Copy_image[Counter] >> 8);
		vidWriteData(Copy_image[Counter] & 0x00ff );

	}
}






void TFT_vidFillColor(const u16 Copy_u16Color )
{
	u16 Counter;
	u8 Data;
	/* Set X Address*/
	vidWriteCommand(0x2A);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(127);

	/* Set Y Address*/
	vidWriteCommand(0x2B);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(0);
	vidWriteData(159);

	/* RAM Write */
	vidWriteCommand(0x2C);

	for (Counter = 0 ; Counter <20480 ; Counter++)
	{
		/* Write The High Byte */
		Data=Copy_u16Color >> 8;
		vidWriteData(Data);
		Data=	Copy_u16Color &	0x00ff;
		vidWriteData(Data );

	}
}







void TFT_vidDrawRect(u8 x1 ,u8 x2 , u8 y1 , u8 y2 , u16 Color_u16Num )
{
	u16 Counter;
	u16 size=(x2-x1)*(y2-y1);
	u8 Data;

	/* Set X Address*/
	vidWriteCommand(0x2A);
	vidWriteData(0);
	vidWriteData(x1);
	vidWriteData(0);
	vidWriteData(x2-1);

	/* Set Y Address*/
	vidWriteCommand(0x2B);
	vidWriteData(0);
	vidWriteData(y1);
	vidWriteData(0);
	vidWriteData(y2-1);

	/* RAM Write */
	vidWriteCommand(0x2C);

	for (Counter = 0 ; Counter <size ; Counter++)
	{
		/* Write The High Byte */

		Data = (Color_u16Num >> 8);
		vidWriteData(Data);
		Data = Color_u16Num  & 0x00ff ;
		vidWriteData(Data);

	}
}




static void vidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp;

	GPIO_vidSetPinVal(TFT_A0_PIN,GPIO_LOW);

	SPI_vidSendReceiveSynch(Copy_u8Command,&Local_u8Temp);


}

static void vidWriteData(u8 Copy_u8Data)
{

	u8 Local_u8Temp;

	GPIO_vidSetPinVal(TFT_A0_PIN,GPIO_HIGH);

	SPI_vidSendReceiveSynch(Copy_u8Data,&Local_u8Temp);


}
