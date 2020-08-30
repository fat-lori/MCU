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
#include "lan8720.h"




#define LOG_TAG "main"
#include "log.h"



int main(void)
{
    //硬件初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
    delay_init(168);            //初始化延时函数
    uart_init(115200);          //初始化串口
    LED_Init();                 //初始化LED端口
    KEY_Init();                 //初始化按键
    TIM3_Int_Init(999,839);     //初始化定时器3，100Hz的频率
    FSMC_SRAM_Init();           //初始化外部SRAM
    LAN8720_Init();             //网口硬件初始化
    LCD_Init();                 //初始化LCD
    printf("\r\n HardWare Init Successful!");



    //软件初始化
    //init_malloc();              //初始化内存池
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
    lock_init();
    LOG_INFO("SofeWare Init Successful!");



    //创建任务函数
    card_setup();


    //开启任务调度
    vTaskStartScheduler();

    return 0;
}



