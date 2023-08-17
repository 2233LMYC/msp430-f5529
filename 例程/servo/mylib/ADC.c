/*
 * ADC.c
 *
 *  Created on: 2023Äê5ÔÂ14ÈÕ
 *      Author: LMTX
 */
#include "ADC.h"


uint16_t ADCValue[6];
float ADCVfinal[6];

void ADC12AInit(void)   //40Mhz / 8 =5Mhz
{
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1+GPIO_PIN2 + GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6);
    // Initialize ADC12 with ADC12¡¯s built-in oscillator
    ADC12_A_init (ADC12_A_BASE,ADC12_A_SAMPLEHOLDSOURCE_SC,ADC12_A_CLOCKSOURCE_SMCLK,ADC12_A_CLOCKDIVIDER_3);
    //Switch ON ADC12
    ADC12_A_enable(ADC12_A_BASE);
    // Setup sampling timer to sample-and-hold for 16 clock cycles
    ADC12_A_setupSamplingTimer (ADC12_A_BASE,ADC12_A_CYCLEHOLD_64_CYCLES,ADC12_A_CYCLEHOLD_4_CYCLES,ADC12_A_MULTIPLESAMPLESENABLE);
    // Configure the Input to the Memory Buffer with the specified Reference Voltages
    ADC12_A_configureMemoryParam param = {0};
    param.memoryBufferControlIndex = ADC12_A_MEMORY_2;
    param.inputSourceSelect = ADC12_A_INPUT_A2;
    param.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
    param.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);

    param.memoryBufferControlIndex = ADC12_A_MEMORY_3;
    param.inputSourceSelect = ADC12_A_INPUT_A3;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);


    param.memoryBufferControlIndex = ADC12_A_MEMORY_1;
    param.inputSourceSelect = ADC12_A_INPUT_A1;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);

    param.memoryBufferControlIndex = ADC12_A_MEMORY_4;
    param.inputSourceSelect = ADC12_A_INPUT_A4;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);

    param.memoryBufferControlIndex = ADC12_A_MEMORY_5;
    param.inputSourceSelect = ADC12_A_INPUT_A5;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);

    param.memoryBufferControlIndex = ADC12_A_MEMORY_6;
    param.inputSourceSelect = ADC12_A_INPUT_A6;
    param.endOfSequence = ADC12_A_ENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);
}

void ADCRead(void)
{
    int i;
    for(i=0;i<7;i++) ADCValue[i]=0;
    for(i=0;i<10;i++)
    {
        // Start a single conversion, no repeating or sequences.
        ADC12_A_startConversion (ADC12_A_BASE,ADC12_A_MEMORY_1,ADC12_A_SEQOFCHANNELS);
        // Wait for the Interrupt Flag to assert
        while( !(ADC12_A_getInterruptStatus(ADC12_A_BASE,ADC12_A_IFG1)) );
        // Clear the Interrupt Flag and start another conversion
        ADC12_A_clearInterrupt(ADC12_A_BASE,ADC12_A_IFG1);
//        ADCValue[0] += 0.1*ADC12MEM0;
        ADCValue[0] += 0.1*ADC12MEM1;
        ADCValue[1] += 0.1*ADC12MEM2;
        ADCValue[2] += 0.1*ADC12MEM3;
        ADCValue[3] += 0.1*ADC12MEM4;
        ADCValue[4] += 0.1*ADC12MEM5;
        ADCValue[5] += 0.1*ADC12MEM6;
       for(i=0;i<9;i++)
       {
           ADCVfinal[i] = ADCValue[i]*3.3/4096;
           ADCVfinal[i] = ADCVfinal[i]*10;
       }
    }
}

