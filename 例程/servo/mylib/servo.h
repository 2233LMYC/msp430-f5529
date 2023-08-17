/*
 * servo.h
 *
 *  Created on: 2023Äê7ÔÂ27ÈÕ
 *      Author: LMTX
 */

#ifndef _SERVO_H_
#define _SERVO_H_

#include "main.h"


void ServerA2PWMInit(void);  //40M/40/20000=50hz
void Server_A2Pwm_Angle(uint8_t REGISTER,int8_t angle);//([1,2],[-90,90])

void Server_B0Pwm_Angle(uint8_t REGISTER,int8_t angle);
void ServerB0PWMInit(void);  //40M/40/20000=50hz



#endif /* MYLIB_SERVO_H_ */
