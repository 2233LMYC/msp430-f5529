/*
 * SYS_it.c
 *
 *  Created on: 2023年7月27日
 *      Author: LMTX
 */

#include "SYS_it.h"
#include "TIMER.h"
#include "LED.h"
#include "inv_mpu.h"

extern float pitch,roll,yaw;

void Timer_A1_Init(void)//40M/10/4000=1ms
{
    Timer_A_initUpModeParam htim = {0};
    htim.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    htim.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_10;
    htim.timerPeriod = 4000;
    htim.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    htim.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    htim.timerClear = TIMER_A_DO_CLEAR;
    htim.startTimer = true;

    Timer_A_initUpMode(TIMER_A1_BASE, &htim);

}

void Timer_B0_Init(void)//40M/10/4000=1ms
{
    Timer_B_initUpModeParam htimB = {0};
    htimB.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
    htimB.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_10;
    htimB.timerPeriod = 4000;
    htimB.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
    htimB.captureCompareInterruptEnable_CCR0_CCIE = TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    htimB.timerClear = TIMER_B_DO_CLEAR;
    htimB.startTimer = true;

    Timer_B_initUpMode(TIMER_B0_BASE, &htimB);

}







#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER_TB0_IRQ_Handler (void)
{
    _EINT();//开总中断
    static int cnt = 0;
        cnt++;
        if(cnt == 100)
        {
            LED2(2);
            cnt = 0;
        }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_TA1_IRQ_Handler (void)
{
    _EINT();//开总中断
    static int cnt = 0;
        cnt++;
        if(cnt == 100)
        {
            LED2(2);
//            mpu_dmp_get_data(&pitch,&roll,&yaw);
            cnt = 0;
        }
}


