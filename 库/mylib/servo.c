/*
 * servo.c
 *
 *  Created on: 2023年7月27日
 *      Author: LMTX
 */

#include "servo.h"
#include "TIMER.h"


void ServerA2PWMInit(void)  //40M/40/20000=50hz
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,GPIO_PIN4+GPIO_PIN5);
    Timer_A_outputPWMParam param2;

    param2.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;//选择时钟源
    param2.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_40;//时钟源40分频
    param2.timerPeriod = 20000;//定时器装载值
    param2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;//初始化捕获比较寄存器1，对应通道TA2.1==>p2.4
    param2.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;//选择输出模式
    param2.dutyCycle = 0;//
    Timer_A_outputPWM(TIMER_A2_BASE,&param2);

    param2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;//初始化捕获比较寄存器2，对应通道TA2.2==>p2.5
    Timer_A_outputPWM(TIMER_A2_BASE,&param2);
}


void ServerB0PWMInit(void)  //40M/40/20000=50hz
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3,GPIO_PIN6+GPIO_PIN5);
    Timer_B_outputPWMParam param2;

    param2.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;//选择时钟源
    param2.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_40;//时钟源40分频
    param2.timerPeriod = 20000;//定时器装载值
    param2.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_5;//初始化捕获比较寄存器1，对应通道TA2.1==>p2.4
    param2.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;//选择输出模式
    param2.dutyCycle = 0;//
    Timer_B_outputPWM(TIMER_B0_BASE,&param2);

    param2.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_6;//初始化捕获比较寄存器2，对应通道TA2.2==>p2.5
    Timer_B_outputPWM(TIMER_B0_BASE,&param2);
}


void Server_B0Pwm_Angle(uint8_t REGISTER,int8_t angle)
{
    switch(REGISTER)
    {
        case 1:
        {
            Timer_B_setCompareValue
            (
                    TIMER_B0_BASE,
                    TIMER_B_CAPTURECOMPARE_REGISTER_5,
                    (uint16_t)(550+(90+angle)*(2000/180))
            );
        }
        break;
        case 2:
        {
            Timer_B_setCompareValue
            (
                    TIMER_B0_BASE,
                    TIMER_B_CAPTURECOMPARE_REGISTER_6,
                    (uint16_t)(550+(90+angle)*(2000/180))
            );
        }
        break;
    }
}

void Server_A2Pwm_Angle(uint8_t REGISTER,int8_t angle)
{
    switch(REGISTER)
    {
        case 1:
        {
            Timer_A_setCompareValue
            (
                    TIMER_A2_BASE,
                    TIMER_A_CAPTURECOMPARE_REGISTER_1,
                    (uint16_t)(550+(90+angle)*(2000/180))
            );
        }
        break;
        case 2:
        {
            Timer_A_setCompareValue
            (
                    TIMER_A2_BASE,
                    TIMER_A_CAPTURECOMPARE_REGISTER_2,
                    (uint16_t)(550+(90+angle)*(2000/180))
            );
        }
        break;
    }
}



