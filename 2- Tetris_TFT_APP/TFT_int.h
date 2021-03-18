/*
 * TFT_int.h
 *
 *  Created on: Sep 21, 2020
 *      Author: eslam
 */

#ifndef TFT_INT_H_
#define TFT_INT_H_


void TFT_vidInit(void);
void TFT_vidDisplayImage(const u16* Copy_image );
void TFT_vidFillColor(const u16 Copy_u16Color );
void TFT_vidDrawRect(u8 x1 ,u8 x2 , u8 y1 , u8 y2 , u16 Color_u16Num );


#endif /* TFT_INT_H_ */
