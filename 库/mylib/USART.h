/*
 * USART.h
 *
 *  Created on: 2023Äê5ÔÂ12ÈÕ
 *      Author: LMTX
 */

#ifndef USER_USART_H_
#define USER_USART_H_


#include "main.h"
#include "stdio.h"

void Usart1Init(void);
void Usart0Init(void);
void send0(unsigned char *ptr,int size);
void send1(unsigned char *ptr,int size);
void usart1_Callback(uint8_t rec0);
void usart0_Callback(uint8_t rec0);



#endif /* USER_USART_H_ */
