/***********************************************************************************
* 文 件 名   : task_manage.c
* 负 责 人   : 罗瑞
* 创建日期   : 2019年12月17日
* 文件描述   : 所有任务的管理源文件
* 版权说明   : Copyright (c) 2008-2019   xx xx xx xx 技术有限公司
* 其    他   : 
* 修改日志   : 
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

//任务句柄
TaskHandle_t StartTask_Handler;
TaskHandle_t LED0Task_Handler;
TaskHandle_t LED1Task_Handler;
TaskHandle_t FLOATTask_Handler;
//定时器计时
volatile UI8_T timer_count,time_1s_count;
void TCPIP_Init(void);


//LED0任务函数 
void led0_task(void *pvParameters)
{
	while(1)
	{
		LED0=~LED0;
		vTaskDelay(500);
	}
}	

//LED1任务函数
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
//浮点测试任务
void float_task(void *pvParameters)
{
	static float float_num=0.00;
    u8 i=0;	    
	u8 *p=0;
    u8 sramx=0;					//默认为内部sram
    
    //测试malloc是否正常
    p=mymalloc(sramx,2048);//申请2K字节
	if(p!=NULL)
        LCD_ShowString(10,30,200,20,16,"Memory Malloc Get successfully");
    else
       LCD_ShowString(10,50,200,20,16,"Memory Malloc Get fail");
     	 
	while(1)
	{
		float_num+=0.01f;
        sprintf((char*)p,"Memory Malloc Test%03d",i);//更新显示内容
        //printf("\r\n%s",p);
        i++;
		//printf("float_num的值为: %.4f\r\n",float_num);
		vTaskDelay(1000);
	}
}
#endif

//命令行任务
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

//软件定时器，回调函数
void vTimerCallback1(xTimerHandle pxTimer)
{		
	if(timer_count++ >= 1)
	{
		time_1s_count++;
		timer_count = 0;

		cli_timeout_count();
	}
}


//发送数据A任务
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


//发送数据B任务
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


//处理数据任务
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



//开始任务任务函数
void start_task(void *pvParameters)
{
	LOG_DEBUG("Hello World!");
	//创建LED0任务
	xTaskCreate((TaskFunction_t )led0_task, 		
				(const char*	)"led0_task",		
				(uint16_t		)LED0_STK_SIZE, 
				(void*			)NULL,				
				(UBaseType_t	)LED0_TASK_PRIO,	
				(TaskHandle_t*	)&LED0Task_Handler);
	
	//创建LED1任务
	xTaskCreate((TaskFunction_t )led1_task, 	
				(const char*	)"led1_task",	
				(uint16_t		)LED1_STK_SIZE, 
				(void*			)NULL,
				(UBaseType_t	)LED1_TASK_PRIO,
				(TaskHandle_t*	)&LED1Task_Handler);
	
	//命令行任务
	xTaskCreate((TaskFunction_t )CliTask,	 
				(const char*	)"cli_task",	 
				(uint16_t		)512, 
				(void*			)NULL,
				(UBaseType_t	)4,
				(TaskHandle_t*	)NULL);
    #if 0
    //浮点测试任务
	xTaskCreate((TaskFunction_t )float_task,	 
				(const char*	)"float_task",	 
				(uint16_t		)FLOAT_STK_SIZE, 
				(void*			)NULL,
				(UBaseType_t	)FLOAT_TASK_PRIO,
				(TaskHandle_t*	)&FLOATTask_Handler); 
    
    //发送数据A任务
    xTaskCreate((TaskFunction_t )sendA_task, 	
				(const char*	)"sendA_task",	
				(uint16_t		)128, 
				(void*			)NULL,
				(UBaseType_t	)2,
				(TaskHandle_t*	)NULL);
    //发送数据B任务
    xTaskCreate((TaskFunction_t )sendB_task, 	
				(const char*	)"sendB_task",	
				(uint16_t		)128, 
				(void*			)NULL,
				(UBaseType_t	)4,
				(TaskHandle_t*	)NULL);
    //处理数据任务
    xTaskCreate((TaskFunction_t )handle_task, 	
				(const char*	)"handle_task",	
				(uint16_t		)512, 
				(void*			)NULL,
				(UBaseType_t	)3,
				(TaskHandle_t*	)NULL);
    #endif
	vTaskDelete(StartTask_Handler); //删除开始任务
}


void card_setup()
{
    
    
    taskENTER_CRITICAL();			//进入临界区，保证临界段中的程序执行不被任何中断打断！

    LOG_DEBUG("Start Task!");
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,			//任务函数
				(const char*	)"start_task",			//任务名称
				(uint16_t		)START_STK_SIZE,		//任务堆栈大小
				(void*			)NULL,					//传递给任务函数的参数
				(UBaseType_t	)START_TASK_PRIO,		//任务优先级
				(TaskHandle_t*	)&StartTask_Handler);	//任务句柄		

	//创建定时器任务	
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

    //创建TCPIP线程
    TCPIP_Init();

    
    taskEXIT_CRITICAL();			//退出临界区
}

	


