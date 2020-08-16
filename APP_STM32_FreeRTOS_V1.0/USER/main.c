#include "sys.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "control.h" 
#include "task.h"
#include "task_manage.h"
#include "lcd.h"
#include "key.h"
#include "sram.h"   
#include "malloc.h"
#include "timer.h"




#define LOG_TAG "main"
#include "log.h"



int main(void)
{
    //硬件初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
    delay_init(168);		//初始化延时函数
    uart_init(115200);     	//初始化串口
    LED_Init();		        //初始化LED端口
    KEY_Init();  			//初始化按键
    LCD_Init(); 			//初始化LCD
    TIM3_Int_Init(999,839); //初始化定时器3，100Hz的频率
    LCD_ShowString(10,10,200,20,16,"HardWare Init Successful!");
    FSMC_SRAM_Init();			//初始化外部SRAM  
    printf("HardWare Init Successful!");
    
    //mymalloc初始化
    my_mem_init(SRAMIN);		//初始化内部内存池
    my_mem_init(SRAMEX);		//初始化外部内存池
    my_mem_init(SRAMCCM);		//初始化CCM内存池

    //软件初始化
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
    lock_init();
    LOG_DEBUG("SofeWare Init Successful!");

    POINT_COLOR = RED; 		
    LCD_ShowString(30,30,200,16,16,"Explorer STM32F4");
    LCD_ShowString(30,90,200,16,16,"2014/8/15"); 


    //创建任务函数
    card_setup();

    //开启任务调度
    vTaskStartScheduler();

    return 0;
}



