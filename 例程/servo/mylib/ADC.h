/*
 * ADC.h
 *
 *  Created on: 2023��5��14��
 *      Author: LMTX
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"

extern uint16_t ADCValue[6];
extern float ADCVfinal[6];


void ADC12AInit(void);
void ADCRead(void);



#endif /* ADC_H_ */
