/*
 * USART.c
 *
 *  Created on: 2023��5��12��
 *      Author: LMTX
 */

#include "USART.h"
#include "string.h"
#include "PID.h"
#include "stdlib.h"

float X_data,Y_data,none=1;

uint8_t receivedData0 = 0x00;
uint8_t reBuff0[20] = {0};

#define MAX_BUFFER_SIZE 20
char receiveBuffer[MAX_BUFFER_SIZE];
int receiveIndex = 0;

void Usart1Init(void)
{
  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN5);
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN4);

  //Baudrate = 115200, clock freq = 4MHz
  //UCBRx = 34, UCBRFx = 6, UCBRSx = 0, UCOS16 = 0
  USCI_A_UART_initParam param = {0};
  param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
  param.clockPrescalar = 347;
  param.firstModReg = 2;
  param.secondModReg = 0;
  param.parity = USCI_A_UART_NO_PARITY;
  param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
  param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
  param.uartMode = USCI_A_UART_MODE;
  param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

  if (STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param))
  {
      return;
  }

  //Enable UART module for operation
  USCI_A_UART_enable(USCI_A1_BASE);

  //Enable Receive Interrupt
  USCI_A_UART_clearInterrupt(USCI_A1_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
  USCI_A_UART_enableInterrupt(USCI_A1_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
}

void Usart0Init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN4 + GPIO_PIN3);
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 347;
    param.firstModReg = 2;
    param.secondModReg = 0;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == USCI_A_UART_init(USCI_A0_BASE, &param)){
        return;
    }

    //Enable UART module for operation
      USCI_A_UART_enable(USCI_A0_BASE);

    //Enable Receive Interrupt
      USCI_A_UART_clearInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
      USCI_A_UART_enableInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
}

/*printf redefine*/

int fputc(int ch,FILE *f)
{
    UCA1TXBUF = ch&0xff;
    while(!(UCA1IFG & UCTXIFG));//�ȴ��������
     return ch;
}
int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++){
    UCA1TXBUF = _ptr[i]&0xff;
    while(!(UCA1IFG & UCTXIFG));//�ȴ��������

  }

  return len;
}


void send0(unsigned char *ptr,int size)    //Send string.
{
    int i = 0;
    for(;i<size;i++)
    {
        USCI_A_UART_transmitData(USCI_A0_BASE,*ptr);
        ptr++;
    }
}

void send1(unsigned char *ptr,int size)    //Send string.
{
    int i = 0;
    for(;i<size;i++)
    {
        USCI_A_UART_transmitData(USCI_A1_BASE,*ptr);
        ptr++;
    }
}


//void usart1_Callback(uint8_t rec1)
//{
//    static char cnt1 = 0;
//
//    reBuff1[cnt1++] = rec1;
//    if(rec1 == '\n')
//    {
//        cnt1 = 0;
//        px = strstr((const char*)reBuff1,(const char*)"X:");
//        py = strstr((char*)reBuff1,(char*)"Y:");
//        if(px != NULL)
//        {
//           while(*px != 'Y')
//           {
//               px = px+pxcnt+2;
//               ser_x[pxcnt++] = *(px);
//           }
//           pid_Servo_x.actual = atof((const char*)ser_x);
//           memset(ser_x,0,5);
//           pxcnt = 0;
//        }
//        if(py != NULL)
//        {
//           while(*py != '\n')
//           {
//               py = px+pycnt+2;
//               ser_y[pycnt++] = *(px);
//           }
//           pid_Servo_y.actual = atof((const char*)ser_y);
//           memset(ser_y,0,5);
//           pycnt = 0;
//        }
//        memset(reBuff1,0,20);
//    }
//
//}

void usart0_Callback(uint8_t rec0)
{
    static char cnt0 = 0;
        if(rec0 != '\n')
            reBuff0[cnt0++] = rec0;
        else
            cnt0 = 0;
}


//******************************************************************************
//
//This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR (void)
{
    uint8_t receivedData = 0;
    switch (__even_in_range(UCA0IV,4))
    {
        //Vector 2 - RXIFG
        case 2:
            receivedData = USCI_A_UART_receiveData(USCI_A0_BASE);
            usart0_Callback(receivedData);
            break;
        default:
            break;
    }
}
//******************************************************************************
//
//This is the USCI_A1 interrupt vector service routine.
//
//******************************************************************************
//#pragma vector=USCI_A1_VECTOR
//__interrupt void USCI_A1_ISR (void)
//{
//    uint8_t receivedData = 0;
//    switch (__even_in_range(UCA1IV,4))
//    {
//        //Vector 2 - RXIFG
//        case 2:
//            receivedData = USCI_A_UART_receiveData(USCI_A1_BASE);
//            usart1_Callback(receivedData);
//            break;
//        default:
//            break;
//    }
//}


#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void)
{
    uint8_t receivedData = 0;
    switch (__even_in_range(UCA1IV,4))
    {
        //Vector 2 - RXIFG
        case 2:
            receivedData = USCI_A_UART_receiveData(USCI_A1_BASE);
            if (receivedData == '\n') // �����յ����з�ʱ����ʾһ������������
            {
                receiveBuffer[receiveIndex] = '\0'; // ����ַ���������
                receiveIndex = 0; // ���ý��ջ���������

                // �����ַ���������"x="��"y="��λ��
                const char*NONE = strstr(receiveBuffer, "None");
                const char*xPosition = strstr(receiveBuffer, "X=");
                const char*yPosition = strstr(receiveBuffer, "Y=");

                if(NONE) none=1;
                else if (xPosition && yPosition) { // ����ҵ�"x="��"y="���������������ֵ
                    X_data = atof(xPosition + 2); // +2��Ϊ������"x="
                    Y_data = atof(yPosition + 2); // +2��Ϊ������"y="
                    none = 0;
                    // ������Զ�xValue��yValue���н�һ������
                    // ���磬�����Ƿ��ͻظ���λ�����������������
                }
            } else
            {
                receiveBuffer[receiveIndex++] = receivedData; // �����յ����ַ���ӵ�������
                if (receiveIndex >= MAX_BUFFER_SIZE) {
                    // ��ֹ�����������������յ������ݳ�����������С�����Խ�����Ӧ����
                    // ���磺��ջ����������ý�������
                    receiveIndex = 0;
                }
            }
            break;
        default:
            break;
    }
}


