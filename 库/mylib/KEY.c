/*
 * KEY.c
 *
 *  Created on: 2023年5月12日
 *      Author: LMTX
 */

#include "KEY.h"
#include "USART.h"


void KEY_Init(void)
{
    //board_key
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,GPIO_PIN1);
}

void KEY_EXIT_Init(void)
{
    //设置输入模式
   GPIO_setAsInputPin (GPIO_PORT_P2, GPIO_PIN1);
   GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN1);
   //选择边缘触发
   GPIO_selectInterruptEdge (GPIO_PORT_P2, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
   GPIO_selectInterruptEdge (GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
   //设置上拉
   GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P2, GPIO_PIN1);
   GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
   //开启引脚中断
   GPIO_enableInterrupt (GPIO_PORT_P2, GPIO_PIN1);//启用引脚上的中断
   GPIO_enableInterrupt (GPIO_PORT_P1, GPIO_PIN1);//启用引脚上的中断

}

//KEY2
#pragma vector=PORT1_VECTOR
__interrupt void Port_2Key(void)
{
    GPIO_disableInterrupt (GPIO_PORT_P1, GPIO_PIN1);
    if(P1IFG&BIT1)
    {
        delay_ms(10);
        if(P1IFG&BIT1)
        {

            send1((unsigned char*)"WORK",4);
        }

    }
    GPIO_enableInterrupt (GPIO_PORT_P1, GPIO_PIN1);//启用引脚上的中断
    GPIO_clearInterrupt (GPIO_PORT_P1, GPIO_PIN1);
}

//KEY1
#pragma vector=PORT2_VECTOR
__interrupt void Port_1Key(void)
{
    GPIO_disableInterrupt (GPIO_PORT_P2, GPIO_PIN1);
    if(P2IFG&BIT1)
    {
        delay_ms(10);
        if(P2IFG&BIT1)
        {

            send1((unsigned char*)"SHIBIE",6);
        }

    }
    GPIO_enableInterrupt (GPIO_PORT_P2, GPIO_PIN1);//启用引脚上的中断
    GPIO_clearInterrupt (GPIO_PORT_P2, GPIO_PIN1);
}
