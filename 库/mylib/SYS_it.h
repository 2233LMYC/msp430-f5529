/*
 * SYS_it.h
 *
 *  Created on: 2023��7��27��
 *      Author: LMTX
 */

#ifndef _SYS_IT_H_
#define _SYS_IT_H_


#include "main.h"

/*
        RTC_VECTOR
        PORT2_VECTOR
        TIMER2_A1_VECTOR
        TIMER2_A0_VECTOR
        USCI_B1_VECTOR
        USCI_A1_VECTOR
        PORT1_VECTOR
        TIMER1_A1_VECTOR
        TIMER1_A0_VECTOR
        DMA_VECTOR
        USB_UBM_VECTOR
        TIMER0_A1_VECTOR
        TIMER0_A0_VECTOR
        ADC12_VECTOR
        USCI_B0_VECTOR
        USCI_A0_VECTOR
        WDT_VECTOR
        TIMER0_B1_VECTOR
        TIMER0_B0_VECTOR
        COMP_B_VECTOR
        UNMI_VECTOR
        SYSNMI_VECTOR
        RESET_VECTOR
 *
  //IO��
  VECTOR_P1            = VECTOR_PORT1,
  VECTOR_P2            = VECTOR_PORT2,
  //SPI
  VECTOR_SPI0          = VECTOR_USCI_A0,
  VECTOR_SPI1          = VECTOR_USCI_A1,
  VECTOR_SPI2          = VECTOR_USCI_B0,
  VECTOR_SPI3          = VECTOR_USCI_B1,
  //I2C
  VECTOR_I2C0          = VECTOR_USCI_B0,
  VECTOR_I2C1          = VECTOR_USCI_B1,
  //UART
  VECTOR_UART0         = VECTOR_USCI_A0,
  VECTOR_UART1         = VECTOR_USCI_A1,
  //TIMER��ע�ⶨʱ���������ж�������CCR0����ռ��һ���ж������������ж�Դ��ͬʹ��һ���ж�����
  VECTOR_TIMER_A0      = VECTOR_TIMER0_A1,
  VECTOR_TIMER_A0_CCR0 = VECTOR_TIMER0_A0,
  VECTOR_TIMER_A1      = VECTOR_TIMER1_A1,
  VECTOR_TIMER_A1_CCR0 = VECTOR_TIMER1_A0,
  VECTOR_TIMER_A2      = VECTOR_TIMER2_A1,
  VECTOR_TIMER_A2_CCR0 = VECTOR_TIMER2_A0,
  VECTOR_TIMER_B0      = VECTOR_TIMER0_B1,
  VECTOR_TIMER_B0_CCR0 = VECTOR_TIMER0_B0,

*/

//TIMERx_A0_VECTOR  // CCR0 ���ж�����
//TIMERx_A1_VECTOR  // TAIV ���ж�����
//TIMER_A_STOP_MODE
//TIMER_A_UP_MODE            //������ģʽ
//TIMER_A_CONTINUOUS_MODE    //��������ģʽ
//TIMER_A_UPDOWN_MODE        //��������ģʽ


//timerPeriod��ָ����Timer_Aʱ��Ρ�����д���ֵ����CCR0������Ϊ16λ[uint16_t]

//timerInterruptEnable_TAIE��ʹ�ܻ���ʧ�ܶ�ʱ���ж�
//TIMER_A_TAIE_INTERRUPT_ENABLE  //ʹ�ܶ�ʱ���ж�
//TIMER_A_TAIE_INTERRUPT_DISABLE  //ʧ�ܶ�ʱ���ж�

//captureCompareInterruptEnable_CCR0_CCIE��ѡ���ж���Ӧ
//TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE    //CCR0�ж�
//TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE   //TAIE�ж�

//timerClear��ѡ���Ƿ�Ѷ�ʱ���Ķ�ʱ����������Ƶ�������ļ���ֵ����
//TIMER_A_DO_CLEAR      //���
//TIMER_A_SKIP_CLEAR    //�����

//startTimer��ѡ���ʼ��֮���Ƿ�����������ʱ��
// true   //��ʼ��������������ʱ��
// false  //��ʼ����������ʱ��

/*
 *
 *
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_TA1_IRQ_Handler (void)
{

}

*/


void Timer_B0_Init(void);//40M/10/4000=1ms
void Timer_A1_Init(void);//40M/10/4000 = 1ms



#endif /* MYLIB_SYS_IT_H_ */
