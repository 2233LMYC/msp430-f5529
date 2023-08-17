/*
 * TIMER.h
 *
 *  Created on: 2023Äê5ÔÂ12ÈÕ
 *      Author: LMTX
 */

#ifndef USER_TIMER_H_
#define USER_TIMER_H_

#include "main.h"

#define TIMER_PERIOD    2000

void Clock_Init(unsigned char Fre);
void timerA0PWMInit(void); //40Mhz/1/2000=20khz
void Fix_A0Pwm_Duty(uint8_t REGISTER,float duty);//([1,4],[0,100])


#endif /* USER_TIMER_H_ */
