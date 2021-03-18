/*
 * SPI_int.h
 *
 *  Created on: Sep 18, 2020
 *      Author: eslam
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_

void SPI_vidInit(void);
void SPI_vidSendReceiveSynch(u8 Copy_u8DataToTransmit , u8 *Copy_DataToReceive);
void SPI_vidSendReceiveASynch(u8 Copy_u8DataToTransmit , void (*CallBack)(u8));
void SPI_vidDisableSPI1(void);

#endif /* SPI_INT_H_ */
