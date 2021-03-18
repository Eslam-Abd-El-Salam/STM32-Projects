/*
 * ESP_int.h
 *
 *  Created on: Oct 21, 2020
 *      Author: eslam
 */

#ifndef ESP_INT_H_
#define ESP_INT_H_


void ESP_vidInit(void);
void ESP_vidConnectWifi(u8 *name , u8 *Pass );
void ESP_vidConnectServer_Tcp(u8 *Domain , u8 *Port );
u8 ESP_u8ReceiveHttpReq( u8 * Copy_u8DNSID , u8 * Copy_u8Length );
void ESP_SendDatatoServer( u8 * Copy_u8DNSID , u8 * Copy_u8Length );
static void clear_Buffer(void);

#endif /* ESP_INT_H_ */
