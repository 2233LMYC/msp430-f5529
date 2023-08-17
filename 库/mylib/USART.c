/*
 * USART.c
 *
 *  Created on: 2023年5月12日
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
    while(!(UCA1IFG & UCTXIFG));//等待发送完成
     return ch;
}
int fputs(const char *_ptr, register FILE *_fp)
{
  unsigned int i, len;

  len = strlen(_ptr);

  for(i=0 ; i<len ; i++){
    UCA1TXBUF = _ptr[i]&0xff;
    while(!(UCA1IFG & UCTXIFG));//等待发送完成

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
            if (receivedData == '\n') // 当接收到换行符时，表示一条完整的数据
            {
                receiveBuffer[receiveIndex] = '\0'; // 添加字符串结束符
                receiveIndex = 0; // 重置接收缓冲区索引

                // 解析字符串，查找"x="和"y="的位置
                const char*NONE = strstr(receiveBuffer, "None");
                const char*xPosition = strstr(receiveBuffer, "X=");
                const char*yPosition = strstr(receiveBuffer, "Y=");

                if(NONE) none=1;
                else if (xPosition && yPosition) { // 如果找到"x="和"y="，则解析其后的整数值
                    X_data = atof(xPosition + 2); // +2是为了跳过"x="
                    Y_data = atof(yPosition + 2); // +2是为了跳过"y="
                    none = 0;
                    // 这里可以对xValue和yValue进行进一步处理
                    // 例如，将它们发送回给上位机或用于其他计算等
                }
            } else
            {
                receiveBuffer[receiveIndex++] = receivedData; // 将接收到的字符添加到缓冲区
                if (receiveIndex >= MAX_BUFFER_SIZE) {
                    // 防止缓冲区溢出，如果接收到的数据超出缓冲区大小，可以进行相应处理
                    // 例如：清空缓冲区，重置接收索引
                    receiveIndex = 0;
                }
            }
            break;
        default:
            break;
    }
}


