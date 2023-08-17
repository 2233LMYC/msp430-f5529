/*
 * TIMER.c
 *
 *  Created on: 2023年5月12日
 *      Author: LMTX
 */

#include "TIMER.h"
#include "LED.h"

void Clock_Init(unsigned char Fre)
{

    P5SEL |= BIT2|BIT3|BIT4|BIT5;//开启外部两个时钟

    UCSCTL6 |= XCAP_3|XT1OFF;          // XT1 相关 配置
    UCSCTL6 |= XT2DRIVE_0 |XT2OFF;     // XT2 相关 配置
//以下是提升核心电压部分的代码
    PMMCTL0_H = 0xA5;                                         //开PMM电源管理
    SVSMLCTL |= SVSMLRRL_1 + SVMLE;                            //配置SVML电压
    PMMCTL0 =  PMMPW + PMMCOREV_3;                             //配置内核电压
    while((PMMIFG & SVSMLDLYIFG ) == 0);                       //等待设置完成
    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG + SVSMLDLYIFG);
    if((PMMIFG & SVMLIFG) == 1)                                //判断内核电压是否上升到VSVML
         while((PMMIFG & SVMLVLRIFG) == 0);                    //如果没有等待
    SVSMLCTL &= ~SVMLE;                                        //关掉SVML模块
    PMMCTL0_H = 0X00;

    __bis_SR_register(SCG0);                 //该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时 MCLK 暂停工作
    UCSCTL0 = 0;                             //先清零，FLL 运行时，该寄存器系统会自动配置，不用管
    UCSCTL6 = (UCSCTL6&(~(XT2OFF|XT1OFF))|XCAP_3|XT2DRIVE_0);
    UCSCTL3 = (5<<4)|(2<<0);                 // 选择 XTAL2 的时钟信号作为参考信号 并且分频到1MHz
    if(Fre < 5)
        UCSCTL1 = DCORSEL_2;
    else if(Fre<15)
        UCSCTL1 = DCORSEL_4;
    else
        UCSCTL1 = DCORSEL_7;
   UCSCTL2 = (Fre-1);
    __bic_SR_register(SCG0);
    __delay_cycles(782000);
    while (SFRIFG1 & OFIFG) {                               // Check OFIFG fault flag
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);           // Clear OSC flaut Flags
      SFRIFG1 &= ~OFIFG;                                    // Clear OFIFG fault flag
    }
    UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;
}


void timerA0PWMInit(void) //40Mhz/1/2000=20khz
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN2+GPIO_PIN3+GPIO_PIN4+GPIO_PIN5);//初始化GPIO
    Timer_A_outputPWMParam param;
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;//选择时钟源
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;//时钟源不分频
    param.timerPeriod = TIMER_PERIOD-1;//定时器装载值
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;//初始化捕获比较寄存器1，对应通道TA0.1==>p1.2
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;//选择输出模式
    param.dutyCycle = TIMER_PERIOD/2;
    Timer_A_outputPWM(TIMER_A0_BASE,&param);

    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;//初始化捕获比较寄存器2，对应通道TA0.2==>p1.3
    Timer_A_outputPWM(TIMER_A0_BASE,&param);
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;//初始化捕获比较寄存器3，对应通道TA0.3==>p1.4
    Timer_A_outputPWM(TIMER_A0_BASE,&param);
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;//初始化捕获比较寄存器4，对应通道TA0.4==>p1.5
    Timer_A_outputPWM(TIMER_A0_BASE,&param);
}

void Fix_A0Pwm_Duty(uint8_t REGISTER,float duty)
{
    switch(REGISTER)
    {
        case 1:
        {
            Timer_A_setCompareValue
            (
                TIMER_A0_BASE,
                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                (uint16_t)(TIMER_PERIOD*(duty/100))
            );

        }break;

        case 2:
        {
            Timer_A_setCompareValue
            (
                TIMER_A0_BASE,
                TIMER_A_CAPTURECOMPARE_REGISTER_2,
                (uint16_t)(TIMER_PERIOD*(duty/100))
            );
        }break;

        case 3:
        {
            Timer_A_setCompareValue
            (
                TIMER_A0_BASE,
                TIMER_A_CAPTURECOMPARE_REGISTER_3,
                (uint16_t)(TIMER_PERIOD*(duty/100))
            );
        }break;
        case 4:
        {
            Timer_A_setCompareValue
            (
                TIMER_A0_BASE,
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                (uint16_t)(TIMER_PERIOD*(duty/100))
            );
        }break;

    }
}






