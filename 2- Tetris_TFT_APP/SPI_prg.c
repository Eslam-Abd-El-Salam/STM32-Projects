/*
 * SPI_prg.c
 *
 *  Created on: Sep 18, 2020
 *      Author: eslam
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"AFIO_int.h"
#include"SPI_int.h"
#include"SPI_priv.h"
#include"SPI_cfg.h"
#include"Dio_int.h"
#include"NVIC_int.h"

static u8 Local_Varaible;
void (*Callback) (u8);

void SPI_vidInit(void)
{

//	MNVIC_vidInit();


	/*      Pin Configuration       */
#if  (SPI_PORT_SELECT == SPI_PORTA)
	{
		MAFIO_vidSetSPICfg(SPI_PORTA);                         // SPI ON PortA
		GPIO_vidSetPinDir(GPIOA,PIN7,OUTPUT_SPEED_10MHZ_AFPP);   //MOSI  A7
		GPIO_vidSetPinDir(GPIOA,PIN6,INPUT_FLOATING);          //MISO   A6
		GPIO_vidSetPinDir(GPIOA,PIN5,OUTPUT_SPEED_10MHZ_AFPP);    // SCK1   A5

		//GPIO_vidSetPinDir(SPI1_SLAVE_PIN,OUTPUT_SPEED_10MHZ_PP);    // SS
	}

#elif  (SPI_PORT_SELECT == SPI_PORTB)
	{
		MAFIO_vidSetSPICfg(SPI_PORTB);                           //SPI ON PortB
		GPIO_vidSetPinDir(GPIOB,PIN5,OUTPUT_SPEED_2MHZ_AFPP);     //MOSI
		GPIO_vidSetPinDir(GPIOB,PIN4,INPUT_FLOATING);            //MISO
		GPIO_vidSetPinDir(GPIOB,PIN3,OUTPUT_SPEED_2MHZ_AFPP);    // SCK1
		GPIO_vidSetPinDir(SPI1_SLAVE_PIN,OUTPUT_SPEED_2MHZ_PP);    // SS
	}



#endif

	/*                 Clock phase Selection                  */

#if (CLOCK_PHASE ==  CAPTURE_IN_FIRST_CLK_TRANSATION )
	{
		CLR_BIT(SPI1->CR1,0);
	}
#elif (CLOCK_PHASE == CAPTURE_IN_SECOND_CLK_TRANSATION)
	{
		SET_BIT(SPI1->CR1,0);                 		     /* Capture data in Second Transition*/
	}

#endif


	/*             Clock Polarity              */


#if (CLOCK_POLARITY ==  LOW_COCK_IDLE )
	{
		CLR_BIT(SPI1->CR1,1);
	}
#elif (CLOCK_POLARITY == HIGH_COCK_IDLE)
	{
		SET_BIT(SPI1->CR1,1);
	}

#endif

	/*           Master Selection                */


#if (MC_MASTER_SLAVE ==  MASTER )
	{
		SET_BIT(SPI1->CR1,2);
	}
#elif (MC_MASTER_SLAVE == SLAVE)
	{
		CLR_BIT(SPI1->CR1,2);
	}

#endif



	/* Select Which Bit To be send First in frame format */

#if (FRAME_FORMAT_SENDING_BIT ==  LSB )
	{
		SET_BIT(SPI1->CR1,7);
	}
#elif (FRAME_FORMAT_SENDING_BIT == MSB)
	{
		CLR_BIT(SPI1->CR1,7);
	}

#endif



	/*       RXONLY   Receive Only or SEnd & Receive             */


#if (RXONLY ==  SEND_RECEIVE )
	{
		CLR_BIT(SPI1->CR1,10);
	}
#elif (RXONLY == RECEIVE_ONLY)
	{
		SET_BIT(SPI1->CR1,10);
	}

#endif

	/*   Select Baud Rate and Enable SPI   */

	SET_BIT(SPI1->CR1,8);
	SET_BIT(SPI1->CR1,9);

	Local_Varaible = BAUD_RATE_SELECTION;
	SPI1->CR1 |=((Local_Varaible)<<3);


}



void SPI_vidSendReceiveSynch(u8 Copy_u8DataToTransmit , u8 *Copy_DataToReceive)
{

	//GPIO_vidSetPinVal(SPI1_SLAVE_PIN,GPIO_LOW);


	/*            Send Data                */

	SPI1->DR = Copy_u8DataToTransmit;

	/* Wait Busy Flag */

	while (GET_BIT(SPI1->SR,7) == 1 );

	/* Received data */

	*Copy_DataToReceive = SPI1->DR  ;

	//GPIO_vidSetPinVal(SPI1_SLAVE_PIN,GPIO_HIGH);

}


void SPI_vidSendReceiveASynch(u8 Copy_u8DataToTransmit , void (*ptr)(u8))
{
	MNVIC_vidEnableInterrupt(35);         //Enable SPI Interrupt from NVIC
	GPIO_vidSetPinVal(SPI1_SLAVE_PIN,GPIO_LOW);


	/*            Send Data                */

	SPI1->DR = Copy_u8DataToTransmit;

	Callback = ptr;


}


void SPI_vidDisableSPI1(void)
{
	CLR_BIT(SPI1->CR1,6);
}



void SPI1_IRQHandler(void)
{

	GPIO_vidSetPinVal(SPI1_SLAVE_PIN,GPIO_HIGH);
	Callback( SPI1->DR);

	SPI_vidDisableSPI1();
	MNVIC_vidDisableInterrupt(35);
}
