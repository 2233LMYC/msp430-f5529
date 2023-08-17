/*
 * control.c
 *
 *  Created on: 2023年7月31日
 *      Author: LMTX
 */

#include "control.h"
#include "PID.h"
#include "servo.h"
#include "ZX_MOTOR.h"
#include "PID.h"




extern float pitch,roll,yaw;
extern float none;
extern PID_struct pid_Servo_x;
extern PID_struct pid_Servo_y;


void ZZYT_Init(void)
{
    Server_B0Pwm_Angle(1,0);
    Server_B0Pwm_Angle(2,0);

    delay_ms(500);

    //X轴
    pid_Servo_x.target = 64;
    pid_Servo_x.Kp = 0.05;
    pid_Servo_x.Ki = 0.05;
    pid_Servo_x.Kd = 0.1;

    //Y轴
    pid_Servo_y.target = 80;
    pid_Servo_y.Kp = -0.03;
    pid_Servo_y.Ki = -0.02;
    pid_Servo_y.Kd = 0;
}



void ZZYT_proc(float x,float y)//追踪云台函数，传入目标的实际坐标
{
    if(x>60&&x<70)
    {
        x = 64;
    }
    if(y>70&&y<90)
    {
        y = 80;
    }

    pid_Servo_x.actual = x;
    pid_Servo_y.actual = y;

    pid_Servo_x.out += Position_PID(&pid_Servo_x);
    pid_Servo_y.out += Position_PID(&pid_Servo_y);

    //y限幅
    if(pid_Servo_y.out >=85) pid_Servo_y.out = 85;
    else if(pid_Servo_y.out <=(-85)) pid_Servo_y.out = -85;
    //x限幅
    if(pid_Servo_x.out >=85) pid_Servo_x.out = 85;
    else if(pid_Servo_x.out <=(-85)) pid_Servo_x.out = -85;

    if(none == 1)
    {
        pid_Servo_x.err_sum = 0;
        pid_Servo_y.err_sum = 0;
        pid_Servo_x.out = 0;
        pid_Servo_y.out = 0;
    }

    Server_B0Pwm_Angle(1,pid_Servo_x.out);
    Server_B0Pwm_Angle(2,pid_Servo_y.out);

}


void Motor_Control(uint8_t id,int32_t rpm)
{
    switch(id)
    {
        case 1:
            if(rpm > 0) Zx_MotorRunS(id,rpm);
            else Zx_MotorRunN(id,-rpm);
            break;
        case 2:
            if(rpm > 0) Zx_MotorRunN(id,rpm);
            else Zx_MotorRunS(id,-rpm);
            break;
        case 3:
            if(rpm > 0) Zx_MotorRunS(id,rpm);
            else Zx_MotorRunN(id,-rpm);
            break;
        case 4:
            if(rpm > 0) Zx_MotorRunN(id,rpm);
            else Zx_MotorRunS(id,-rpm);
            break;
    }
}

void Car_move_Proc(int sta)//车辆运动控制，输入对应状态（forward,back,left,right,stop）
{
    if(sta == stop)
    {
        Motor_Control(LF_Motor,0);
        Motor_Control(LB_Motor,0);
        Motor_Control(RF_Motor,0);
        Motor_Control(RB_Motor,0);
    }
    else if(sta == forward)
    {
        Motor_Control(LF_Motor,forward_speed);
        Motor_Control(LB_Motor,forward_speed);
        Motor_Control(RF_Motor,forward_speed);
        Motor_Control(RB_Motor,forward_speed);
    }
    else if(sta == back)
    {
        Motor_Control(LF_Motor,back_speed);
        Motor_Control(LB_Motor,back_speed);
        Motor_Control(RF_Motor,back_speed);
        Motor_Control(RB_Motor,back_speed);
    }

    else if(sta == left)
    {
        Motor_Control(LF_Motor,left_L_speed);
        Motor_Control(LB_Motor,left_L_speed);
        Motor_Control(RF_Motor,left_R_speed);
        Motor_Control(RB_Motor,left_R_speed);
    }
    else if(sta == right)
    {
        Motor_Control(LF_Motor,right_L_speed);
        Motor_Control(LB_Motor,right_L_speed);
        Motor_Control(RF_Motor,right_R_speed);
        Motor_Control(RB_Motor,right_R_speed);
    }

}


