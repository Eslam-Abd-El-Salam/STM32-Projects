/*
 * SPI_cfg.h
 *
 *  Created on: Sep 18, 2020
 *      Author: eslam
 */

#ifndef SPI_CFG_H_
#define SPI_CFG_H_

/* Select Slave Pin and port  */

#define SPI1_SLAVE_PIN    GPIOA,PIN0
#define SPI_PORT_SELECT   SPI_PORTA                //Select APIO FOR SPI  SPI_PORTA or SPI_PORTB


/* Select Which Bit To be send First in frame format */
/* MSB                                               */
/* LSB                                               */
/*****************************************************/

#define  FRAME_FORMAT_SENDING_BIT    MSB



/* Clock phase Selection                  */
/*  CAPTURE_IN_FIRST_CLK_TRANSATION       */
/*  CAPTURE_IN_SECOND_CLK_TRANSATION      */
/******************************************/

#define CLOCK_PHASE    CAPTURE_IN_SECOND_CLK_TRANSATION


/*             Clock Polarity              */
/* LOW_COCK_IDLE                           */
/* HIGH_COCK_IDLE                          */
/*******************************************/

#define CLOCK_POLARITY     HIGH_COCK_IDLE



/*             Master Selection             */
/*  SLAVE                                   */
/*  MASTER                                  */
/********************************************/

#define MC_MASTER_SLAVE       MASTER


/* RXONLY                      */
/* RECEIVE_ONLY                */
/* SEND_RECEIVE                */
/*******************************/

#define   RXONLY      SEND_RECEIVE





/* BAUD RATE SELECTION            */
/*   FPLCK_DIV_2                  */
/*   FPLCK_DIV_4                  */
/*   FPLCK_DIV_8                  */
/*   FPLCK_DIV_16                 */
/*   FPLCK_DIV_32                 */
/*   FPLCK_DIV_64                 */
/*   FPLCK_DIV_128                */
/*   FPLCK_DIV_256                */
/**********************************/


#define  BAUD_RATE_SELECTION    FPLCK_DIV_2



/* Pin Port Selection  */
/*
 *SPI_PORTA
 *SPI_PORTB
 *
 ******************************************/




#endif /* SPI_CFG_H_ */
