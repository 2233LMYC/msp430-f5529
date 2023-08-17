/*
 * SYS_it.h
 *
 *  Created on: 2023年7月27日
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
  //IO口
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
  //TIMER，注意定时器有两个中断向量，CCR0单独占用一个中断向量，其他中断源共同使用一个中断向量
  VECTOR_TIMER_A0      = VECTOR_TIMER0_A1,
  VECTOR_TIMER_A0_CCR0 = VECTOR_TIMER0_A0,
  VECTOR_TIMER_A1      = VECTOR_TIMER1_A1,
  VECTOR_TIMER_A1_CCR0 = VECTOR_TIMER1_A0,
  VECTOR_TIMER_A2      = VECTOR_TIMER2_A1,
  VECTOR_TIMER_A2_CCR0 = VECTOR_TIMER2_A0,
  VECTOR_TIMER_B0      = VECTOR_TIMER0_B1,
  VECTOR_TIMER_B0_CCR0 = VECTOR_TIMER0_B0,

*/

//TIMERx_A0_VECTOR  // CCR0 的中断向量
//TIMERx_A1_VECTOR  // TAIV 的中断向量
//TIMER_A_STOP_MODE
//TIMER_A_UP_MODE            //增计数模式
//TIMER_A_CONTINUOUS_MODE    //连续计数模式
//TIMER_A_UPDOWN_MODE        //增减计数模式


//timerPeriod：指定的Timer_A时间段。这是写入的值进入CCR0。限制为16位[uint16_t]

//timerInterruptEnable_TAIE：使能还是失能定时器中断
//TIMER_A_TAIE_INTERRUPT_ENABLE  //使能定时器中断
//TIMER_A_TAIE_INTERRUPT_DISABLE  //失能定时器中断

//captureCompareInterruptEnable_CCR0_CCIE：选择中断响应
//TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE    //CCR0中断
//TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE   //TAIE中断

//timerClear：选择是否把定时器的定时计数器，分频计数器的计数值清零
//TIMER_A_DO_CLEAR      //清除
//TIMER_A_SKIP_CLEAR    //不清除

//startTimer：选择初始化之后是否立即启动定时器
// true   //初始化后立即启动定时器
// false  //初始化后不启动定时器

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
