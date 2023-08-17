/*
 * control.h
 *
 *  Created on: 2023年7月31日
 *      Author: LMTX
 */

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "main.h"



#define forward_speed   150//直走速度
#define back_speed      -100//倒车速度

#define left_L_speed    100//左转左电机速度
#define left_R_speed    150//左转右电机速度

#define right_L_speed   150//右转左电机速度
#define right_R_speed   100//右转右电机速度




enum state{

    forward = 1,
    back,
    stop,
    left,
    right,

};


void Motor_Control(uint8_t id,int32_t rpm);
void Car_move_Proc(int sta);//车辆运动控制，输入对应状态（forward,back,left,right,stop）


void ZZYT_proc(float x,float y);//追踪云台函数，传入目标的实际坐标
void ZZYT_Init(void);





#endif /* MYLIB_CONTROL_H_ */
