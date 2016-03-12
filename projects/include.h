/******************** (C) COPYRIGHT 2012-2013 �Ĭ�Ƽ� DEMOK*********
 * �ļ���       ��include.h
 * ����         ������ģ��ͷ�ļ�
 *
 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

* ����޶�ʱ��    ��2012-11-6
* �޶�����        ����
**********************************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
#include  "gpio.h"      //IO�ڲ���
#include  "delay.h"      //IO�ڲ���
#include  "dma.h"
#include  "uart.h"      //����
#include  "adc.h"       //ADCģ��
#include  "FTM.h"       //FTMģ�飨FTM0��������� / ͨ�� /PWM     FTM1��2���������� / ͨ�� /PWM ��
#include  "PIT.h"       //�����жϼ�ʱ��
#include  "lptmr.h"     //�͹��Ķ�ʱ��(��ʱ)
#include  "exti.h"      //EXTI�ⲿGPIO�ж�
#include  "arm_math.h"  //DSP��
#include  "sccb.h"      //SCCB��
#include  "key.h"
#include  "PID.h"
#include  "servorPID.h"

#include  "camera.h"


#define ROW 240               //����
#define COL 320               //����
#define PicSize  ROW*COL      //ͼ���С
#define THRESHOLD 140
#define HANG 3
#define OFFSET  20              //�����е�����Ұ�е��ƫ��


/***************** ucos ר�� *****************/
#define USOC_EN     0u      //0Ϊ��ֹuC/OS������0������uC/OS
#if USOC_EN > 0u
#include  "ucos_ii.h"  		//uC/OS-IIϵͳ����ͷ�ļ�
#include  "BSP.h"			//�뿪������صĺ���
#include  "app.h"			//�û�������


#endif  //if  USOC_EN > 0


#endif  //__INCLUDE_H__