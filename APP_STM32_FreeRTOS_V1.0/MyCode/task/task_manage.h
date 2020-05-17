/***********************************************************************************
 * �� �� ��   : task_manage.h
 * �� �� ��   : ����
 * ��������   : 2019��12��17��
 * �ļ�����   : taskmanage.c ��ͷ�ļ�
 * ��Ȩ˵��   : Copyright (c) 2008-2019   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
***********************************************************************************/

#ifndef __TASKMANAGE_H__
#define __TASKMANAGE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "task.h"

extern TaskHandle_t StartTask_Handler;
extern TaskHandle_t LED0Task_Handler;
extern TaskHandle_t LED1Task_Handler;
extern TaskHandle_t FLOATTask_Handler;

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  



//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  



//�������ȼ�
#define LED1_TASK_PRIO		3
//�����ջ��С	
#define LED1_STK_SIZE 		50  


//�������ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		128




extern void float_task(void *pvParameters);
extern void led0_task(void *pvParameters);
extern void led1_task(void *pvParameters);
extern void start_task(void *pvParameters);
extern void card_setup(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TASKMANAGE_H__ */
