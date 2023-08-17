/*
 * control.h
 *
 *  Created on: 2023��7��31��
 *      Author: LMTX
 */

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "main.h"



#define forward_speed   150//ֱ���ٶ�
#define back_speed      -100//�����ٶ�

#define left_L_speed    100//��ת�����ٶ�
#define left_R_speed    150//��ת�ҵ���ٶ�

#define right_L_speed   150//��ת�����ٶ�
#define right_R_speed   100//��ת�ҵ���ٶ�




enum state{

    forward = 1,
    back,
    stop,
    left,
    right,

};


void Motor_Control(uint8_t id,int32_t rpm);
void Car_move_Proc(int sta);//�����˶����ƣ������Ӧ״̬��forward,back,left,right,stop��


void ZZYT_proc(float x,float y);//׷����̨����������Ŀ���ʵ������
void ZZYT_Init(void);





#endif /* MYLIB_CONTROL_H_ */
