/*
 * SPI_priv.h
 *
 *  Created on: Sep 18, 2020
 *      Author: eslam
 */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

typedef struct{


	volatile u32    CR1       ;
	volatile u32    CR2       ;
	volatile u32    SR        ;
	volatile u32    DR        ;
	volatile u32    CRCPR     ;
	volatile u32    RXCRCR    ;
	volatile u32    TXCRCR    ;
	volatile u32    I2SCFGR   ;
	volatile u32    I2SPR     ;




}Spi_Register;



#define SPI1     ((volatile Spi_Register*)0x40013000)


/* Frame Format Bit */
#define LSB   1
#define MSB   0




/* Clock phase */
#define  CAPTURE_IN_FIRST_CLK_TRANSATION   0
#define  CAPTURE_IN_SECOND_CLK_TRANSATION  1



/* Clock Polarity */
#define   LOW_COCK_IDLE   0
#define   HIGH_COCK_IDLE   1




/*Master Selection */
#define SLAVE    0
#define MASTER   1




/* BAUD RATE SELECTION */

#define FPLCK_DIV_2     0b1000
#define FPLCK_DIV_4     0b1001
#define FPLCK_DIV_8     0b1010
#define FPLCK_DIV_16    0b1011
#define FPLCK_DIV_32    0b1100
#define FPLCK_DIV_64    0b1101
#define FPLCK_DIV_128   0b1110
#define FPLCK_DIV_256   0b1111




/* RXONLY */

#define RECEIVE_ONLY      1
#define SEND_RECEIVE      0

/* Pin Port Selection  */

#define     SPI_PORTA       0
#define     SPI_PORTB       1


#endif /* SPI_PRIV_H_ */
