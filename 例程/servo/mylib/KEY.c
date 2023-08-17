/*
 * KEY.c
 *
 *  Created on: 2023��5��12��
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
    //��������ģʽ
   GPIO_setAsInputPin (GPIO_PORT_P2, GPIO_PIN1);
   GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN1);
   //ѡ���Ե����
   GPIO_selectInterruptEdge (GPIO_PORT_P2, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
   GPIO_selectInterruptEdge (GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
   //��������
   GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P2, GPIO_PIN1);
   GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
   //���������ж�
   GPIO_enableInterrupt (GPIO_PORT_P2, GPIO_PIN1);//���������ϵ��ж�
   GPIO_enableInterrupt (GPIO_PORT_P1, GPIO_PIN1);//���������ϵ��ж�

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
    GPIO_enableInterrupt (GPIO_PORT_P1, GPIO_PIN1);//���������ϵ��ж�
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
    GPIO_enableInterrupt (GPIO_PORT_P2, GPIO_PIN1);//���������ϵ��ж�
    GPIO_clearInterrupt (GPIO_PORT_P2, GPIO_PIN1);
}
