/*
 * KEY.h
 *
 *  Created on: 2023Äê5ÔÂ12ÈÕ
 *      Author: LMTX
 */

#ifndef USER_KEY_H_
#define USER_KEY_H_

#include "main.h"

#define  key1    GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1)
#define  key2    GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN1)

void KEY_Init(void);
void KEY_EXIT_Init(void);



#endif /* USER_KEY_H_ */
