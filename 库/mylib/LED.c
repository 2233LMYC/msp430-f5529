/*
 * LED.c
 *
 *  Created on: 2023Äê5ÔÂ12ÈÕ
 *      Author: LMTX
 */


#include "LED.h"


void LED_Init(void)
{
    //board_led
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN7);
}

void LED1(u8 pre)
{
    if (pre == 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
    else if(pre == 0){
        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
    else if(pre == 2){
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
}

void LED2(u8 pre)
{
    if (pre == 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN7);
    }
    else if(pre == 0){
        GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN7);
    }
    else if(pre == 2){
        GPIO_toggleOutputOnPin(GPIO_PORT_P4,GPIO_PIN7);
    }
}


