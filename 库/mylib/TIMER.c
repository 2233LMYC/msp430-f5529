/*
 * TIMER.c
 *
 *  Created on: 2023��5��12��
 *      Author: LMTX
 */

#include "TIMER.h"
#include "LED.h"

void Clock_Init(unsigned char Fre)
{

    P5SEL |= BIT2|BIT3|BIT4|BIT5;//�����ⲿ����ʱ��

    UCSCTL6 |= XCAP_3|XT1OFF;          // XT1 ��� ����
    UCSCTL6 |= XT2DRIVE_0 |XT2OFF;     // XT2 ��� ����
//�������������ĵ�ѹ���ֵĴ���
    PMMCTL0_H = 0xA5;                                         //��PMM��Դ����
    SVSMLCTL |= SVSMLRRL_1 + SVMLE;                            //����SVML��ѹ
    PMMCTL0 =  PMMPW + PMMCOREV_3;                             //�����ں˵�ѹ
    while((PMMIFG & SVSMLDLYIFG ) == 0);                       //�ȴ��������
    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG + SVSMLDLYIFG);
    if((PMMIFG & SVMLIFG) == 1)                                //�ж��ں˵�ѹ�Ƿ�������VSVML
         while((PMMIFG & SVMLVLRIFG) == 0);                    //���û�еȴ�
    SVSMLCTL &= ~SVMLE;                                        //�ص�SVMLģ��
    PMMCTL0_H = 0X00;

    __bis_SR_register(SCG0);                 //���﷨Ϊ�̶���ʽ����Ϊ�������ڵı�����λ��SCG0��ϵͳ����ģʽ�йأ���ʱ MCLK ��ͣ����
    UCSCTL0 = 0;                             //�����㣬FLL ����ʱ���üĴ���ϵͳ���Զ����ã����ù�
    UCSCTL6 = (UCSCTL6&(~(XT2OFF|XT1OFF))|XCAP_3|XT2DRIVE_0);
    UCSCTL3 = (5<<4)|(2<<0);                 // ѡ�� XTAL2 ��ʱ���ź���Ϊ�ο��ź� ���ҷ�Ƶ��1MHz
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
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN2+GPIO_PIN3+GPIO_PIN4+GPIO_PIN5);//��ʼ��GPIO
    Timer_A_outputPWMParam param;
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;//ѡ��ʱ��Դ
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;//ʱ��Դ����Ƶ
    param.timerPeriod = TIMER_PERIOD-1;//��ʱ��װ��ֵ
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;//��ʼ������ȽϼĴ���1����Ӧͨ��TA0.1==>p1.2
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;//ѡ�����ģʽ
    param.dutyCycle = TIMER_PERIOD/2;
    Timer_A_outputPWM(TIMER_A0_BASE,&param);

    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;//��ʼ������ȽϼĴ���2����Ӧͨ��TA0.2==>p1.3
    Timer_A_outputPWM(TIMER_A0_BASE,&param);
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;//��ʼ������ȽϼĴ���3����Ӧͨ��TA0.3==>p1.4
    Timer_A_outputPWM(TIMER_A0_BASE,&param);
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;//��ʼ������ȽϼĴ���4����Ӧͨ��TA0.4==>p1.5
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






