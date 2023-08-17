#include "main.h"
#include "TIMER.h"
#include "servo.h"
#include "LED.h"
#include "SYS_it.h"
#include "USART.h"
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "KEY.h"
#include "ZX_MOTOR.h"
#include "OLED.h"
#include "PID.h"
#include "string.h"
#include "control.h"

u8 buff[20] = {0};//oled显示缓存

float pitch,roll,yaw;







extern PID_struct pid_Servo_x;
extern PID_struct pid_Servo_y;
extern float X_data,Y_data,none;//串口获得的XY坐标
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Clock_Init(40);
	Timer_A1_Init();
	LED_Init();
	Usart1Init();
	Usart0Init();
	KEY_EXIT_Init();
	OLED_Init();
//	ServerB0PWMInit();
//	MPU_Init();
//	while(mpu_dmp_init());



    __bis_SR_register(GIE);//开EA

    Zx_MotorSetLED(LB_Motor,1);
    Zx_MotorSetLED(LF_Motor,1);
    Zx_MotorSetLED(RB_Motor,1);
    Zx_MotorSetLED(RF_Motor,1);

    Motor_Control(LB_Motor,0);
    Motor_Control(LF_Motor,0);
    Motor_Control(RB_Motor,0);
    Motor_Control(RF_Motor,0);


	while(1)
	{

//	    memset(buff,0,20);
//	    sprintf((char*)buff,"yaw:%.2f",yaw);
//	    OLED_ShowString(0, 0, buff, 12);

	    Car_move_Proc(forward);
	    delay_ms(1000);
	    Car_move_Proc(stop);
	    delay_ms(1000);
	    Car_move_Proc(left);
        delay_ms(1000);
        Car_move_Proc(stop);
        delay_ms(1000);
        Car_move_Proc(right);
        delay_ms(1000);
        Car_move_Proc(stop);
        delay_ms(1000);
        Car_move_Proc(back);
        delay_ms(1000);
        Car_move_Proc(stop);
        delay_ms(1000);

	}
}


