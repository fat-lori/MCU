/***********************************************************************************
* �� �� ��   : task_manage.c
* �� �� ��   : ����
* ��������   : 2019��12��17��
* �ļ�����   : ��������Ĺ���Դ�ļ�
* ��Ȩ˵��   : Copyright (c) 2008-2019   xx xx xx xx �������޹�˾
* ��    ��   : 
* �޸���־   : 
***********************************************************************************/
#include <stdio.h>
#include "basetype.h"
#include "led.h"
#include "delay.h"
#include "cli.h"
#include "malloc.h"	
#include "lcd.h"
#include "control.h"
#include "timers.h"
#include "task_manage.h"

#include "log.h"
#define LOG_TAG     "task"

//������
TaskHandle_t StartTask_Handler;
TaskHandle_t LED0Task_Handler;
TaskHandle_t LED1Task_Handler;
TaskHandle_t FLOATTask_Handler;
//��ʱ����ʱ
volatile UI8_T timer_count,time_1s_count;
void TCPIP_Init(void);


//LED0������ 
void led0_task(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(500);
	}
}	

//LED1������
void led1_task(void *pvParameters)
{
	while(1)
	{
		LED1=0;
		vTaskDelay(200);
		LED1=1;
		vTaskDelay(800);
	}
}

#if 0
//�����������
void float_task(void *pvParameters)
{
	static float float_num=0.00;
    u8 i=0;	    
	u8 *p=0;
    u8 sramx=0;					//Ĭ��Ϊ�ڲ�sram
    
    //����malloc�Ƿ�����
    p=mymalloc(sramx,2048);//����2K�ֽ�
	if(p!=NULL)
        LCD_ShowString(10,30,200,20,16,"Memory Malloc Get successfully");
    else
       LCD_ShowString(10,50,200,20,16,"Memory Malloc Get fail");
     	 
	while(1)
	{
		float_num+=0.01f;
        sprintf((char*)p,"Memory Malloc Test%03d",i);//������ʾ����
        //printf("\r\n%s",p);
        i++;
		//printf("float_num��ֵΪ: %.4f\r\n",float_num);
		vTaskDelay(1000);
	}
}
#endif

//����������
void CliTask(void *pvParameters)
{
    while(1)
    {
        if(user_index>0)
     	{
     	 	cli_MainProcess();
     	}
     	else
    	{
    		cli_UserLogin();
			
    	}    
		msleep(50);
    }
}

//�����ʱ�����ص�����
void vTimerCallback1(xTimerHandle pxTimer)
{		
	if(timer_count++ >= 1)
	{
		time_1s_count++;
		timer_count = 0;

		cli_timeout_count();
	}
}


//��������A����
void sendA_task(void *pvParameters)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int i = 0;
    
    while(1)
    {
        for(i=0; i<10; i++)
        {
            if(xQueueSend(get_queue(QUEUE_SRC_TEST), a+i, 0) != pdPASS)
        	{
        		printf("A queue send error!\r\n");
        	}
            
            printf("send data A:  %d\r\n",*(a+i));
        }
        
		msleep(1000);
    }
}


//��������B����
void sendB_task(void *pvParameters)
{
    int b = 100;
    while(1)
    {
        if(xQueueSendToFront(get_queue(QUEUE_SRC_TEST), &b, 0) != pdPASS)
    	{
    		printf("                      B queue send error!\r\n");
    	}
        printf("                      send data B:  %d\r\n", b);
		msleep(8000);
    }
}


//������������
void handle_task(void *pvParameters)
{
    int i = 0;
    int handle = 0;
    while(1)
    {
        xQueueReceive(get_queue(QUEUE_SRC_TEST), &handle, portMAX_DELAY);
        if(handle == 100)
        {
            for(i=0; i<100000; i++)
            {   }
            printf("                      data B: %d\r\n",handle);
        }
        else
        {
             for(i=0; i<5000000; i++)
            {   }
            msleep(500);
            printf("data A:  %d\r\n",handle);
        }
    }
}



//��ʼ����������
void start_task(void *pvParameters)
{
	LOG_DEBUG("Hello World!");
	//����LED0����
	xTaskCreate((TaskFunction_t )led0_task, 		
				(const char*	)"led0_task",		
				(uint16_t		)LED0_STK_SIZE, 
				(void*			)NULL,				
				(UBaseType_t	)LED0_TASK_PRIO,	
				(TaskHandle_t*	)&LED0Task_Handler);
	
	//����LED1����
	xTaskCreate((TaskFunction_t )led1_task, 	
				(const char*	)"led1_task",	
				(uint16_t		)LED1_STK_SIZE, 
				(void*			)NULL,
				(UBaseType_t	)LED1_TASK_PRIO,
				(TaskHandle_t*	)&LED1Task_Handler);
	
	//����������
	xTaskCreate((TaskFunction_t )CliTask,	 
				(const char*	)"cli_task",	 
				(uint16_t		)512, 
				(void*			)NULL,
				(UBaseType_t	)4,
				(TaskHandle_t*	)NULL);
    #if 0
    //�����������
	xTaskCreate((TaskFunction_t )float_task,	 
				(const char*	)"float_task",	 
				(uint16_t		)FLOAT_STK_SIZE, 
				(void*			)NULL,
				(UBaseType_t	)FLOAT_TASK_PRIO,
				(TaskHandle_t*	)&FLOATTask_Handler); 
    
    //��������A����
    xTaskCreate((TaskFunction_t )sendA_task, 	
				(const char*	)"sendA_task",	
				(uint16_t		)128, 
				(void*			)NULL,
				(UBaseType_t	)2,
				(TaskHandle_t*	)NULL);
    //��������B����
    xTaskCreate((TaskFunction_t )sendB_task, 	
				(const char*	)"sendB_task",	
				(uint16_t		)128, 
				(void*			)NULL,
				(UBaseType_t	)4,
				(TaskHandle_t*	)NULL);
    //������������
    xTaskCreate((TaskFunction_t )handle_task, 	
				(const char*	)"handle_task",	
				(uint16_t		)512, 
				(void*			)NULL,
				(UBaseType_t	)3,
				(TaskHandle_t*	)NULL);
    #endif
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
}


void card_setup()
{
    
    
    taskENTER_CRITICAL();			//�����ٽ�������֤�ٽ���еĳ���ִ�в����κ��жϴ�ϣ�

    LOG_DEBUG("Start Task!");
	//������ʼ����
	xTaskCreate((TaskFunction_t )start_task,			//������
				(const char*	)"start_task",			//��������
				(uint16_t		)START_STK_SIZE,		//�����ջ��С
				(void*			)NULL,					//���ݸ��������Ĳ���
				(UBaseType_t	)START_TASK_PRIO,		//�������ȼ�
				(TaskHandle_t*	)&StartTask_Handler);	//������		

	//������ʱ������	
	TimerHandle_t timer_hdl;
	if((timer_hdl = xTimerCreate("vTimer0",500/portTICK_PERIOD_MS,pdTRUE,0,vTimerCallback1)) == NULL)
	{
		printf("Failed to create softtimer!"); 
		while(1);
	}
	else
	{
		if(xTimerStart(timer_hdl,100) != pdPASS)
			printf("Failed to start softtimer!"); 
	}

    //����TCPIP�߳�
    TCPIP_Init();

    
    taskEXIT_CRITICAL();			//�˳��ٽ���
}

	


