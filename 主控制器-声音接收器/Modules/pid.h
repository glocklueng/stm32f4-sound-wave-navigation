#ifndef __PID_H__
#define __PID_H__

#include "stm32f4xx.h"

typedef struct{
	float limit;	//����޷�
	float deadband;	//����
	float target;	//Ŀ�������
	float feedback;	//ʵ�������	
	float A;	//e(k)��ϵ��
	float B;	//e(k-1)��ϵ��
	float C;	//e(k-2)��ϵ��
	float e_0;	//��ǰ���
	float e_1;	//��һ�����
	float e_2;	//���ϴ����
}PID;

float pid_calc(PID *pid);

#endif
