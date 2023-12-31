/*
 * OLED.h
 *
 *  Created on: 2023年5月14日
 *      Author: LMTX
 */

#ifndef OLED_H_
#define OLED_H_


#include "main.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64
//-----------------OLED IIC端口定义----------------

#define OLED_SCLK_Clr() GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2)//SCL
#define OLED_SCLK_Set() GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2)

#define OLED_SDIN_Clr() GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN1)//SDA
#define OLED_SDIN_Set() GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1)


#define OLED_CMD  0 //写命令
#define OLED_DATA 1 //写数据


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void OLED_IIC_Start();
void OLED_IIC_Stop();
void OLED_Write_IIC_Command(unsigned char IIC_Command);
void OLED_Write_IIC_Data(unsigned char IIC_Data);
void OLED_Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_IIC_Wait_Ack();





#endif /* OLED_H_ */
