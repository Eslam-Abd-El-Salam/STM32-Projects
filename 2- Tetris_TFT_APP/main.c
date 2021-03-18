/*
 * main.c
 *
 *  Created on: Sep 21, 2020
 *      Author: eslam
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"AFIO_int.h"
#include"RCC_int.h"
#include"NVIC_int.h"
#include "TFT_int.h"
#include"Dio_int.h"
#include"SysTick_int.h"
#include"EXTI_int.h"

volatile s8 i;
u8 Occupied_Postion[16][16]= {0};     // 64 * 80  Pairs Pixels to make Square  in x and y
u8 Color_Flag[16][16]={0};
u8 Speed=0;
u8 Y1_Axis;
u8 Y2_Axis;
s8 X1_Axis;
u8 X2_Axis;
u8 Shift=0;
u16 Color;
u8 LVL_UP_Flag=0;
u32 Time_Speed =0 ;
void Shape_1(void);
void Shape_2(void);
void Shape_3(void);

void Square_Postion_Check(void);
void Game_Over(void);
void LVL_UP(void);
//void Shift_Right(void);
//void Shift_Left(void);
u8 Rotating_Flag=0;
s8 Y_Rotate_Shift = 0 ;
s8 X_Rtotate_Shift =0;
s8 Y_Rotate_Shift_Alone_point=0;
u8 X_Rotate_Shift_Alone_point=0;
u8 L_Rotating_Flag=0;
u8 sum=0;
const u8 arr_x1[16]={0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120};
const u8 arr_x2[16]={8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128};
const u8 arr_y1[16]={0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
const u8 arr_y2[16]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};



int main (void)
{

	RCC_vidInitSysClock();
	RCC_vidEnableClock(APB2,2);    // Enable Clock For PORTA
	RCC_vidEnableClock(APB2,12);   // Enable Clock for SPI1
	RCC_vidEnableClock(APB2,0);    // Enable Clock For AFIO
	GPIO_vidSetPinDir(GPIOA,PIN0,INPUT_PULL_DOWN_UP);
	GPIO_vidSetPinVal(GPIOA,PIN0,GPIO_HIGH);
	GPIO_vidSetPinDir(GPIOA,PIN1,INPUT_PULL_DOWN_UP);
	GPIO_vidSetPinVal(GPIOA,PIN1,GPIO_HIGH);
	GPIO_vidSetPinDir(GPIOA,PIN4,INPUT_PULL_DOWN_UP);
	GPIO_vidSetPinVal(GPIOA,PIN4,GPIO_HIGH);






	MSTK_vidInit();
	/*MNVIC_vidInit();

	MEXTI_vidInit(1,LINE_0);    // INIT Mode and line
	MEXTI_vidInit(1,LINE_1);
	MEXTI_vidEnableEXTI(LINE_0);
	MEXTI_vidEnableEXTI(LINE_1);
	MNVIC_vidEnableInterrupt(6);
	MNVIC_vidEnableInterrupt(7);*/

	TFT_vidInit();
	TFT_vidFillColor(0XFFFF);
	TFT_vidDrawRect( 0 , 128 ,150  , 160 ,0x07E6);

	i = 0;
	Speed=10;

	//MEXTI_vidSetCallBack(LINE_0,Shift_Right);
	//MEXTI_vidSetCallBack(LINE_1,Shift_Left);

	while (1)
	{

		Shape_1();
		Shape_2();
		Shape_3();

	}

	return 0;

}






void Square_Postion_Check(void)
{
	u8 Empty;
	for (u8 Again=0; Again <=14 ;Again++)
	{

		for (u8 index_y =0 ;index_y <= 15;index_y++)
		{
			sum=0;
			for(u8 index_x=0 ;index_x <= 15;index_x++ )
			{

				sum = sum+Occupied_Postion[index_x][index_y];
				if (sum ==16 )
				{
					TFT_vidDrawRect( 0  ,128  , arr_y1[index_y]  ,arr_y2[index_y]  , 0xFFFF);
					LVL_UP_Flag++;
					if (LVL_UP_Flag == 3)
					{
						LVL_UP();
						LVL_UP_Flag=0;
						Time_Speed=400000;
						if (Time_Speed == 0)
						{
							Time_Speed=500000;
						}

					}
					for (u8 index_Fill=0 ; index_Fill <=15 ;index_Fill++)
					{
						Occupied_Postion[index_Fill][index_y]=0;

					}

					for (u8 index_Fill = index_y ; index_Fill < 15 ;index_Fill++)   // Shifting The Ones Down And Fill White Color in old place Fill Brown Color In The new Place
					{
						for (u8 index_Fx=0 ; index_Fx <=15 ;index_Fx++)
						{
							if (Occupied_Postion[index_Fx][index_Fill+1]==1)
							{
								Occupied_Postion[index_Fx][index_Fill+1]=0;
								Empty=Color_Flag[index_Fx][index_Fill+1];
								Color_Flag[index_Fx][index_Fill+1]=0;

								TFT_vidDrawRect(  arr_x1[index_Fx]  , arr_x2[index_Fx]  , arr_y1[index_Fill+1]  ,arr_y2[index_Fill+1]  , 0xFFFF);
								Occupied_Postion[index_Fx][index_Fill]= 1;
								Color_Flag[index_Fx][index_Fill]=Empty;

								if (Empty == 1)
								{
									Color =0xF800;
								}
								else if(Empty == 2)
								{
									Color=0xFF80;
								}


								else if(Empty == 3)
								{
									Color=0x189F ;
								}

								TFT_vidDrawRect(  arr_x1[index_Fx]  , arr_x2[index_Fx]  , arr_y1[index_Fill]  ,arr_y2[index_Fill]  , Color);

							}
						}



					}


				}
			}
		}


	}

}


void Game_Over(void)
{
	TFT_vidFillColor(0x0000);
	TFT_vidDrawRect( 0 , 128 ,150  , 160 ,0x07E6);
	TFT_vidDrawRect( arr_x1[11] , arr_x2[14] ,arr_y1[13]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[15] , arr_x2[15] ,arr_y1[10]   , arr_y2[12] , 0xF800);
	TFT_vidDrawRect( arr_x1[11] , arr_x2[14] ,arr_y1[9]   , arr_y2[9] , 0xF800);
	TFT_vidDrawRect( arr_x1[11] , arr_x2[11] ,arr_y1[9]   , arr_y2[10] , 0xF800);
	TFT_vidDrawRect( arr_x1[10] , arr_x2[12] ,arr_y1[11]   , arr_y2[11] , 0xF800);
	/**********************************************************************************/
	TFT_vidDrawRect( arr_x1[4] , arr_x2[4] ,arr_y1[9]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[8] , arr_x2[8] ,arr_y1[9]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[5] , arr_x2[5] ,arr_y1[13]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[7] , arr_x2[7] ,arr_y1[13]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[6] , arr_x2[6] ,arr_y1[12]   , arr_y2[12] , 0xF800);
	/**********************************************************************************/
	TFT_vidDrawRect( arr_x1[2] , arr_x2[2] ,arr_y1[9]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[0] , arr_x2[2] ,arr_y1[13]   , arr_y2[13] , 0xF800);
	TFT_vidDrawRect( arr_x1[0] , arr_x2[2] ,arr_y1[11]   , arr_y2[11] , 0xF800);
	TFT_vidDrawRect( arr_x1[0] , arr_x2[2] ,arr_y1[9]   , arr_y2[9] , 0xF800);
	/*************************************************************************************/



	TFT_vidDrawRect( arr_x1[15] , arr_x2[15] ,arr_y1[3]   , arr_y2[5] , 0xFF80);
	TFT_vidDrawRect( arr_x1[13] , arr_x2[14] ,arr_y1[6]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[13] , arr_x2[14] ,arr_y1[2]   , arr_y2[2] , 0xFF80);
	TFT_vidDrawRect( arr_x1[12] , arr_x2[12] ,arr_y1[3]   , arr_y2[5] , 0xFF80);
	/**********************************************************************************/
	TFT_vidDrawRect( arr_x1[10] , arr_x2[10] ,arr_y1[3]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[8] , arr_x2[8] ,arr_y1[3]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[9] , arr_x2[9] ,arr_y1[2]   , arr_y2[2] , 0xFF80);

	/**********************************************************************************/
	TFT_vidDrawRect( arr_x1[6] , arr_x2[6] ,arr_y1[2]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[4] , arr_x2[5] ,arr_y1[6]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[4] , arr_x2[5] ,arr_y1[4]   , arr_y2[4] , 0xFF80);
	TFT_vidDrawRect( arr_x1[4] , arr_x2[5] ,arr_y1[2]   , arr_y2[2] , 0xFF80);
	/*************************************************************************************/
	TFT_vidDrawRect( arr_x1[2] , arr_x2[2] ,arr_y1[2]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[1] , arr_x2[1] ,arr_y1[3]   , arr_y2[4] , 0xFF80);
	TFT_vidDrawRect( arr_x1[1] , arr_x2[1] ,arr_y1[6]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[0] , arr_x2[0] ,arr_y1[4]   , arr_y2[6] , 0xFF80);
	TFT_vidDrawRect( arr_x1[0] , arr_x2[0] ,arr_y1[2]   , arr_y2[2] , 0xFF80);
	/*************************************************************************************/

	//	TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0xFFC5);
	while(1);


}

void Shape_1(void)
{
	u8 Flag_End_Finite_loop =0;
	for (;;)
	{

		u8 Location_Flag_Full =0;

		if (GPIO_vidGetPinVal(GPIOA,0) == 0)
		{
			Shift -=8;
		}

		if (GPIO_vidGetPinVal(GPIOA,1) == 0)
		{
			Shift +=8;
		}


		if (GPIO_vidGetPinVal(GPIOA,4) == 0)
		{
			if (Rotating_Flag == 0)
			{
				X_Rtotate_Shift = 8;
				Y_Rotate_Shift = 10;
				Rotating_Flag++;
			}
			else
			{
				X_Rtotate_Shift =0;
				Y_Rotate_Shift = 0;
				Rotating_Flag=0;

			}

		}
		Y2_Axis = 150;
		Y1_Axis = 140;
		X1_Axis = 64+Shift;
		X2_Axis = 72+Shift;

		u8 cube_1_Y1 = Y1_Axis-0 -i*Speed ;
		u8 cube_1_Y2 = Y2_Axis-0 -i*Speed ;

		if (X2_Axis >=128)
		{
			X2_Axis = 128;
		}

		if (X1_Axis >=120)
		{
			X1_Axis = 120;
		}

		if (X1_Axis <= 0)
		{
			X1_Axis = 0;
		}
		if (X2_Axis <= 8)
		{
			X2_Axis = 8;
		}

		TFT_vidDrawRect( X1_Axis + X_Rtotate_Shift, X2_Axis + X_Rtotate_Shift, cube_1_Y1 - Y_Rotate_Shift     , cube_1_Y2 - Y_Rotate_Shift    , 0xF800);
		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0xF800);
		TFT_vidDrawRect( X1_Axis - X_Rtotate_Shift, X2_Axis - X_Rtotate_Shift, cube_1_Y1-20 + Y_Rotate_Shift , cube_1_Y2-20 + Y_Rotate_Shift, 0xF800);


		if ((Occupied_Postion[((X1_Axis+X_Rtotate_Shift)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2 ] == 1))
		{
			Location_Flag_Full=1;
		}

		if (Rotating_Flag == 1)
		{
			if(Occupied_Postion[((X1_Axis)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2]== 1)
			{
				Location_Flag_Full=1;

			}

		}


		if (Rotating_Flag == 1)
		{
			if(Occupied_Postion[((X1_Axis-X_Rtotate_Shift)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2]== 1)
			{
				Location_Flag_Full=1;

			}

		}


		MSTK_vidSetBusyWait(500000-Time_Speed);

		if ((((Y1_Axis+Y_Rotate_Shift-20)-(i*Speed)) <= 0) | (Location_Flag_Full == 1) )
		{

			Occupied_Postion[(X1_Axis+X_Rtotate_Shift)/8][((Y2_Axis - Y_Rotate_Shift -(i*Speed))-10)/10] = 1;
			Color_Flag[(X1_Axis+X_Rtotate_Shift)/8][((Y2_Axis - Y_Rotate_Shift -(i*Speed))-10)/10] = 1;

			Occupied_Postion[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]=1;
			Color_Flag[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]= 1;
			Occupied_Postion[(X1_Axis-X_Rtotate_Shift)/8 ][((Y2_Axis + Y_Rotate_Shift -20)-(i*Speed)-10)/10]=1;
			Color_Flag[(X1_Axis-X_Rtotate_Shift)/8 ][((Y2_Axis + Y_Rotate_Shift -20)-(i*Speed)-10)/10]=1;

			Shift=0;
			i = 0;
			Y_Rotate_Shift = 0 ;
			X_Rtotate_Shift =0;
			Rotating_Flag=0;
			sum=0;

			Square_Postion_Check();
			// Check Game over
			for (u8 index_Last =0;index_Last < 15 ;index_Last++)
			{


				if ((Occupied_Postion[index_Last][14] == 1) && (Occupied_Postion[index_Last][13] == 1))
				{
					Game_Over();
				}
			}
			Flag_End_Finite_loop = 1;
			goto End;
		}

		TFT_vidDrawRect( X1_Axis + X_Rtotate_Shift, X2_Axis + X_Rtotate_Shift, cube_1_Y1 - Y_Rotate_Shift     , cube_1_Y2 - Y_Rotate_Shift    , 0xFFFF);
		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0xFFFF);
		TFT_vidDrawRect( X1_Axis - X_Rtotate_Shift, X2_Axis - X_Rtotate_Shift, cube_1_Y1-20 + Y_Rotate_Shift , cube_1_Y2-20 + Y_Rotate_Shift, 0xFFFF);
		i++;


		End:

		if (Flag_End_Finite_loop == 1)
			break;
	}

}

void Shape_2(void)
{
	u8 Flag_End_Finite_loop =0;
	for (;;)
	{

		u8 Location_Flag_Full =0;

		if (GPIO_vidGetPinVal(GPIOA,0) == 0)
		{
			Shift -=8;
		}

		if (GPIO_vidGetPinVal(GPIOA,1) == 0)
		{
			Shift +=8;
		}



		Y2_Axis = 150;
		Y1_Axis = 140;
		X1_Axis = 64+Shift;
		X2_Axis = 72+Shift;

		u8 cube_1_Y1 = Y1_Axis-0 -i*Speed ;
		u8 cube_1_Y2 = Y2_Axis-0 -i*Speed ;

		if (X2_Axis >=128)
		{
			X2_Axis = 128;
		}

		if (X1_Axis >=120)
		{
			X1_Axis = 120;
		}

		if (X1_Axis <= 0)
		{
			X1_Axis = 0;
		}
		if (X2_Axis <= 8)
		{
			X2_Axis = 8;
		}

		TFT_vidDrawRect( X1_Axis, X2_Axis , cube_1_Y1     , cube_1_Y2    , 0xFF80);
		TFT_vidDrawRect( X1_Axis -8 , X2_Axis -8 , cube_1_Y1  , cube_1_Y2, 0xFF80);

		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0xFF80);
		TFT_vidDrawRect( X1_Axis -8, X2_Axis -8 , cube_1_Y1-10  , cube_1_Y2-10 , 0xFF80);

		if ((Occupied_Postion[((X1_Axis)/8)][((cube_1_Y2-10)/10)-2 ] == 1) |(Occupied_Postion[((X1_Axis-8)/8)][((cube_1_Y2-10)/10)-2 ] == 1))
		{
			Location_Flag_Full=1;
		}



		MSTK_vidSetBusyWait(500000-Time_Speed);

		if ((((Y1_Axis-10)-(i*Speed)) <= 0) | (Location_Flag_Full == 1) )
		{

			Occupied_Postion[(X1_Axis)/8][((Y2_Axis -(i*Speed))-10)/10] = 1;
			Occupied_Postion[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]=1;
			Occupied_Postion[(X1_Axis-8)/8 ][((Y2_Axis -10)-(i*Speed)-10)/10]=1;
			Occupied_Postion[(X1_Axis-8)/8 ][((Y2_Axis -(i*Speed))-10)/10]=1;

			Color_Flag[(X1_Axis)/8][((Y2_Axis -(i*Speed))-10)/10] = 2;
			Color_Flag[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]=2;
			Color_Flag[(X1_Axis-8)/8 ][((Y2_Axis -10)-(i*Speed)-10)/10]=2;
			Color_Flag[(X1_Axis-8)/8 ][((Y2_Axis -(i*Speed))-10)/10]=2;



			Shift=0;
			i = 0;
			Y_Rotate_Shift = 0 ;
			X_Rtotate_Shift =0;
			Rotating_Flag=0;
			sum=0;

			Square_Postion_Check();
			// Check Game over
			for (u8 index_Last =0;index_Last < 15 ;index_Last++)
			{


				if ((Occupied_Postion[index_Last][14] == 1) && (Occupied_Postion[index_Last][13] == 1))
				{
					Game_Over();
				}
			}
			Flag_End_Finite_loop =1;
			goto End;
		}



		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1     , cube_1_Y2    , 0XFFFF);
		TFT_vidDrawRect( X1_Axis -8 , X2_Axis -8 , cube_1_Y1  , cube_1_Y2, 0XFFFF);

		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0XFFFF);
		TFT_vidDrawRect( X1_Axis -8, X2_Axis -8 , cube_1_Y1-10  , cube_1_Y2-10 , 0XFFFF);

		i++;
		End:

		if (Flag_End_Finite_loop ==1)
			break;
	}



}

void Shape_3(void)
{
	u8 Flag_End_Finite_loop =0;
	for (;;)
	{

		u8 Location_Flag_Full =0;

		if (GPIO_vidGetPinVal(GPIOA,0) == 0)
		{
			Shift -=8;
		}

		if (GPIO_vidGetPinVal(GPIOA,1) == 0)
		{
			Shift +=8;
		}


		if (GPIO_vidGetPinVal(GPIOA,4) == 0)
		{
			if (Rotating_Flag == 0)
			{
				X_Rtotate_Shift = 8;
				Y_Rotate_Shift = 10;

				Rotating_Flag++;

				if (L_Rotating_Flag == 0)
				{
					Y_Rotate_Shift_Alone_point=20;
					X_Rotate_Shift_Alone_point=0;
					L_Rotating_Flag++;

				}

				else if (L_Rotating_Flag == 2)
				{

					Y_Rotate_Shift_Alone_point=0;
					L_Rotating_Flag++;
				}

			}
			else
			{
				X_Rtotate_Shift =0;
				Y_Rotate_Shift = 0;
				Rotating_Flag=0;
				if (L_Rotating_Flag == 1)
				{
					X_Rotate_Shift_Alone_point=16;
					Y_Rotate_Shift_Alone_point=20;
					L_Rotating_Flag++;
				}

				else if (L_Rotating_Flag == 3)
				{
					X_Rotate_Shift_Alone_point=0;
					Y_Rotate_Shift_Alone_point=0;
					L_Rotating_Flag=0;
				}


			}

		}
		Y2_Axis = 150;
		Y1_Axis = 140;
		X1_Axis = 64+Shift;
		X2_Axis = 72+Shift;

		u8 cube_1_Y1 = Y1_Axis-0 -i*Speed ;
		u8 cube_1_Y2 = Y2_Axis-0 -i*Speed ;

		if (X2_Axis >=128)
		{
			X2_Axis = 128;
		}

		if (X1_Axis >=120)
		{
			X1_Axis = 120;
		}

		if (X1_Axis <= 0)
		{
			X1_Axis = 0;
		}
		if (X2_Axis <= 8)
		{
			X2_Axis = 8;
		}

		TFT_vidDrawRect( X1_Axis + X_Rtotate_Shift, X2_Axis + X_Rtotate_Shift, cube_1_Y1 - Y_Rotate_Shift     , cube_1_Y2 - Y_Rotate_Shift    , 0x189F);
		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0x189F);
		TFT_vidDrawRect( X1_Axis - X_Rtotate_Shift, X2_Axis - X_Rtotate_Shift, cube_1_Y1-20 + Y_Rotate_Shift , cube_1_Y2-20 + Y_Rotate_Shift, 0x189F);
		TFT_vidDrawRect( X1_Axis-8+X_Rotate_Shift_Alone_point , X2_Axis-8 +X_Rotate_Shift_Alone_point, cube_1_Y1-20 + Y_Rotate_Shift_Alone_point , cube_1_Y2-20 + Y_Rotate_Shift_Alone_point, 0x189F);

		if ((Occupied_Postion[((X1_Axis+X_Rtotate_Shift)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2 ] == 1) )
		{
			Location_Flag_Full=1;
		}

		if (Rotating_Flag == 1)
		{
			if(Occupied_Postion[((X1_Axis)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2]== 1)
			{
				Location_Flag_Full=1;

			}

		}


		if (Rotating_Flag == 1)
		{
			if(Occupied_Postion[((X1_Axis-X_Rtotate_Shift)/8)][((cube_1_Y2+Y_Rotate_Shift-20)/10)-2]== 1)
			{
				Location_Flag_Full=1;

			}

		}

		if (L_Rotating_Flag == 2)
		{
			if(Occupied_Postion[(X1_Axis-8+X_Rotate_Shift_Alone_point)/8][((cube_1_Y2+Y_Rotate_Shift)/10)-2]== 1)
			{
				Location_Flag_Full=1;

			}

		}

		if (L_Rotating_Flag == 3)
		{
			if(Occupied_Postion[(X1_Axis-8+X_Rotate_Shift_Alone_point)/8][((cube_1_Y2+Y_Rotate_Shift-20)/10)-3]== 1)
			{
				Location_Flag_Full=1;

			}

		}


		MSTK_vidSetBusyWait(500000-Time_Speed);

		if ((((Y1_Axis+Y_Rotate_Shift-20)-(i*Speed)) <= 0) | (Location_Flag_Full == 1) )
		{

			Occupied_Postion[(X1_Axis+X_Rtotate_Shift)/8][((Y2_Axis - Y_Rotate_Shift -(i*Speed))-10)/10] = 1;
			Color_Flag[(X1_Axis+X_Rtotate_Shift)/8][((Y2_Axis - Y_Rotate_Shift -(i*Speed))-10)/10] = 3;

			Occupied_Postion[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]=1;
			Color_Flag[(X1_Axis)/8 ][((Y2_Axis-10-i*Speed)-10)/10]= 3;
			Occupied_Postion[(X1_Axis-X_Rtotate_Shift)/8 ][((Y2_Axis + Y_Rotate_Shift -20)-(i*Speed)-10)/10]=1;
			Color_Flag[(X1_Axis-X_Rtotate_Shift)/8 ][((Y2_Axis + Y_Rotate_Shift -20)-(i*Speed)-10)/10]=3;
			Occupied_Postion[(X1_Axis-8+X_Rotate_Shift_Alone_point)/8 ][((Y2_Axis + Y_Rotate_Shift_Alone_point -20)-(i*Speed)-10)/10]=1;
			Color_Flag[(X1_Axis-8+X_Rotate_Shift_Alone_point)/8 ][((Y2_Axis + Y_Rotate_Shift_Alone_point -20)-(i*Speed)-10)/10]=3;

			Shift=0;
			i = 0;
			Y_Rotate_Shift = 0 ;
			X_Rtotate_Shift =0;
			Y_Rotate_Shift_Alone_point=0;
			Rotating_Flag=0;
			L_Rotating_Flag=0;
			sum=0;

			Square_Postion_Check();
			// Check Game over
			for (u8 index_Last =0;index_Last < 15 ;index_Last++)
			{


				if ((Occupied_Postion[index_Last][14] == 1) && (Occupied_Postion[index_Last][13] == 1))
				{
					Game_Over();
				}
			}
			Flag_End_Finite_loop = 1;
			goto End;
		}

		TFT_vidDrawRect( X1_Axis + X_Rtotate_Shift, X2_Axis + X_Rtotate_Shift, cube_1_Y1 - Y_Rotate_Shift     , cube_1_Y2 - Y_Rotate_Shift    , 0xFFFF);
		TFT_vidDrawRect( X1_Axis , X2_Axis , cube_1_Y1-10  , cube_1_Y2-10 , 0xFFFF);
		TFT_vidDrawRect( X1_Axis - X_Rtotate_Shift, X2_Axis - X_Rtotate_Shift, cube_1_Y1-20 + Y_Rotate_Shift , cube_1_Y2-20 + Y_Rotate_Shift, 0xFFFF);
		TFT_vidDrawRect( X1_Axis-8+X_Rotate_Shift_Alone_point , X2_Axis-8 +X_Rotate_Shift_Alone_point, cube_1_Y1-20 + Y_Rotate_Shift_Alone_point , cube_1_Y2-20 + Y_Rotate_Shift_Alone_point, 0xFFFF);
		i++;


		End:

		if (Flag_End_Finite_loop == 1)
			break;
	}

}

void LVL_UP(void)
{

	TFT_vidFillColor(0X0000);
	TFT_vidDrawRect( 0 , 128 ,150  , 160 ,0x07E6);

	TFT_vidDrawRect( arr_x1[13] , arr_x2[13] ,arr_y1[8]  , arr_y2[13] ,0xDB41);
	TFT_vidDrawRect( arr_x1[10] , arr_x2[12] ,arr_y1[8]  , arr_y2[8] ,0xDB41);
	/************************************************************************************/

	TFT_vidDrawRect( arr_x1[8] , arr_x2[8] ,arr_y1[9]  , arr_y2[13] ,0xDB41);
	TFT_vidDrawRect( arr_x1[7] , arr_x2[7] ,arr_y1[8]  , arr_y2[8] ,0xDB41);
	TFT_vidDrawRect( arr_x1[6] , arr_x2[6] ,arr_y1[9]  , arr_y2[13] ,0xDB41);
	/************************************************************************************/

	TFT_vidDrawRect( arr_x1[4] , arr_x2[4] ,arr_y1[8]  , arr_y2[13] ,0xDB41);
	TFT_vidDrawRect( arr_x1[1] , arr_x2[3] ,arr_y1[8]  , arr_y2[8] ,0xDB41);
	/************************************************************************************/

	TFT_vidDrawRect( arr_x1[7] , arr_x2[7] ,arr_y1[1]  , arr_y2[6] ,0xF819);
	TFT_vidDrawRect( arr_x1[4] , arr_x2[4] ,arr_y1[3]  , arr_y2[3] ,0xF819);
	TFT_vidDrawRect( arr_x1[5] , arr_x2[5] ,arr_y1[4]  , arr_y2[4] ,0xF819);
	TFT_vidDrawRect( arr_x1[6] , arr_x2[6] ,arr_y1[5]  , arr_y2[5] ,0xF819);
	TFT_vidDrawRect( arr_x1[8] , arr_x2[8] ,arr_y1[5]  , arr_y2[5] ,0xF819);
	TFT_vidDrawRect( arr_x1[9] , arr_x2[9] ,arr_y1[4]  , arr_y2[4] ,0xF819);
	TFT_vidDrawRect( arr_x1[10] , arr_x2[10] ,arr_y1[3]  , arr_y2[3] ,0xF819);


	/************************************************************************************/

	MSTK_vidSetBusyWait(3000000);
	TFT_vidFillColor(0XFFFF);
	TFT_vidDrawRect( 0 , 128 ,150  , 160 ,0x07E6);

}
/*void Shift_Right(void)
{
	Shift -= 8;
}


void Shift_Left(void)
{
	Shift += 8;
}*/
