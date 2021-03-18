/*
 * ESP_prg.c
 *
 *  Created on: Oct 21, 2020
 *      Author: eslam
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"USART_interface.h"
#include"ESP_int.h"
#include"ESP_cfg.h"
#include"ESP_priv.h"


u8 Wifi_flag=0;
u8 Server_flag=0;
u8 Length_Flag=0;
u8 Return_Flag=0;
u8 Data_Transmit_flag=0;
u8  Check_Result_Flag =0;
u8 Local_u8Result_OF_Req=0;
u8 Record_array[100]={0};
u8* Record(void);
void ESP_vidInit(void)
{

	u8 	Local_u8Result = 0;

	while(Local_u8Result == 0)
	{

		/* Stop Echo */
		MUSART1_voidTransmit((u8 *)"ATE0\r\n");
		Local_u8Result = vidESPValidateCmd();
	}



	Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		/* Set Statoin Mode  */

		MUSART1_voidTransmit((u8 *)"AT+CWMODE=1\r\n");
		Local_u8Result = vidESPValidateCmd();
	}



}

static void clear_Buffer(void)
{
	for (u8 i=0;i<100;i++)
	{
		Record_array[i]=0;
	}

}


void ESP_vidConnectWifi(u8 *name , u8 *Pass )
{

	u8 	Local_u8Result = 0;

	while(Local_u8Result == 0)
	{
		MUSART1_voidTransmit((u8 *)"AT+CWJAP_CUR=\"");
		MUSART1_voidTransmit((u8 *)name);
		MUSART1_voidTransmit((u8 *)"\",\"");
		MUSART1_voidTransmit((u8 *)Pass);
		MUSART1_voidTransmit((u8 *)"\"\r\n");
		Wifi_flag=1;
		Local_u8Result = vidESPValidateCmd();
	}



}



void ESP_vidConnectServer_Tcp(u8 *Domain , u8 *Port )
{
	u8 	Local_u8Result = 0;
	Check_Result_Flag=0;
	Local_u8Result_OF_Req=0;
	Data_Transmit_flag=0;
	while(Local_u8Result == 0)
	{

		MUSART1_voidTransmit((u8 *)"AT+CIPSTART=\"TCP\",\"");
		MUSART1_voidTransmit((u8 *)Domain);
		MUSART1_voidTransmit((u8 *)"\",");
		MUSART1_voidTransmit((u8 *)Port);
		MUSART1_voidTransmit((u8 *)"\r\n");
		Server_flag=1;
		Local_u8Result = vidESPValidateCmd();
	}

}




u8 ESP_u8ReceiveHttpReq( u8 * Copy_u8DNSID , u8 * Copy_u8Length )
{
	Local_u8Result_OF_Req  =0;
	u8 Result=0;

	while(Check_Result_Flag == 0)
	{
		while(Local_u8Result_OF_Req == 0)
		{
			MUSART1_voidTransmit( (u8 *) "AT+CIPSEND=" );
			MUSART1_voidTransmit( (u8 *) Copy_u8Length );
			MUSART1_voidTransmit( (u8 *) "\r\n" );
			Length_Flag=1;
			Local_u8Result_OF_Req = vidESPValidateCmd();
		}

		Return_Flag=1;
		MUSART1_voidTransmit( (u8 *) "GET http://" );
		MUSART1_voidTransmit( (u8 *) Copy_u8DNSID );
		MUSART1_voidTransmit( (u8 *) "/record.txt\r\n" );
		Result = vidESPValidateCmd();



	}

	return Result;
}






void ESP_SendDatatoServer( u8 * Copy_u8DNSID , u8 * Copy_u8Length)
{
	u8 Result=0;

	while(Data_Transmit_flag == 0)
	{
		while(Local_u8Result_OF_Req == 0)
		{
			MUSART1_voidTransmit( (u8 *) "AT+CIPSEND=" );
			MUSART1_voidTransmit( (u8 *) Copy_u8Length );
			MUSART1_voidTransmit( (u8 *) "\r\n" );
			Length_Flag=1;
			Local_u8Result_OF_Req = vidESPValidateCmd();
		}

		Data_Transmit_flag=1;
		MUSART1_voidTransmit( (u8  *) "GET http://" );
		MUSART1_voidTransmit( (u8  *) Copy_u8DNSID );
		MUSART1_voidTransmit( (u8  *) "\r\n" );
		Result = vidESPValidateCmd();

	}


}


u8* Record(void)
{
	return Record_array;
}


u8 vidESPValidateCmd(void)
{
	u8 Local_u8Response[100]= {0};
	u8 i = 0;
	u8 Dummy = 0;
	u8 Result= 0;

	while(Dummy != 255)
	{
		if (Wifi_flag==1)
		{
			Dummy = USART1_vidReceiveForWifiOnly();
		}
		else
		{
			Dummy= USART1_vidReceive();
		}
		Local_u8Response[i] = Dummy;
		i++;
	}

	/* Check if ok */
	if (Wifi_flag == 1)
	{
		if ((Local_u8Response[22] == 'C')  && (Local_u8Response[23] == 'O') && (Local_u8Response[24] == 'N')&& (Local_u8Response[25] == 'N'))
		{
			Result = 1;
			Wifi_flag=0;
		}
	}
	else if (Server_flag==1)
	{
		if (((Local_u8Response[11] == 'O')  && (Local_u8Response[12] == 'K')) |((Local_u8Response[0] == 'A')  && (Local_u8Response[1] == 'L'))|((Local_u8Response[1] == 'A')  && (Local_u8Response[2] == 'L'))|((Local_u8Response[1] == 'C')  && (Local_u8Response[2] == 'O')))
		{
			Result = 1;
			Server_flag=0;
		}


	}




	else if (Length_Flag==1)
	{
		if ((Local_u8Response[2] == 'O')  && (Local_u8Response[3] == 'K') )
		{
			Result = 1;
			Length_Flag=0;
		}
		else
		{
			ESP_vidConnectServer_Tcp((u8 *)"205.144.171.99",(u8 *)"80" );  // connect to server
		}
	}


	else if(Data_Transmit_flag==1)
	{

		if (((Local_u8Response[31] == 'I')  && (Local_u8Response[32] == 'P')&& (Local_u8Response[33] == 'D'))&&( (Local_u8Response[37] == 'S')| (Local_u8Response[38] == 'S' )))
		{
			Data_Transmit_flag=2;


		}
		else
		{
			Data_Transmit_flag=0;
			ESP_vidConnectServer_Tcp((u8 *)"205.144.171.99",(u8 *)"80" );  // connect to server
		}


	}



	else if(Return_Flag==1)
	{

		if ((Local_u8Response[31] == 'I')  && (Local_u8Response[32] == 'P')&& (Local_u8Response[33] == 'D')&&( (Local_u8Response[36] == ':')| (Local_u8Response[37] == ':' )))
		{
			Check_Result_Flag=1;
			Return_Flag=0;
			clear_Buffer();
			u8 n=0;
			u8 i;
			if (Local_u8Response[36] == ':')
			{

				i=37;
				while(Local_u8Response[i] !='\n')
				{
					Record_array[n]=Local_u8Response[i];
					n++;
					i++;
				}
				Record_array[n]=Local_u8Response[i];
			}
			else
			{

				i=38;
				while(Local_u8Response[i] !='\n')
				{
					Record_array[n]=Local_u8Response[i];
					n++;
					i++;
				}
				Record_array[n]=Local_u8Response[i];

			}


			return 1;
		}
		else
		{
			Return_Flag=0;
			Result=0;
			Check_Result_Flag=0;
			ESP_vidConnectServer_Tcp((u8 *)"205.144.171.99",(u8 *)"80" );  // connect to server


			if((Record_array[8]=='1')|(Record_array[8]=='\0'))
			{
				Check_Result_Flag=1;
			}


		}

	}

	else
	{
		if ((Local_u8Response[2] == 'O')  && (Local_u8Response[3] == 'K') )
		{
			Result = 1;

		}
	}
	return Result;
}
