#include "sys.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task_manage.h"
#include "lcd.h"
#include "key.h"
#include "control.h" 
#include "sram.h"   
#include "malloc.h"
#include "timer.h"
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"



#define LOG_TAG "main"
#include "log.h"



int main(void)
{
    //硬件初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
	KEY_Init();  			//按键初始化
	LCD_Init(); 			//LCD初始化
	LCD_ShowString(10,10,200,20,16,"HardWare Init Successful!");
	FSMC_SRAM_Init();			//初始化外部SRAM  
	
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	my_mem_init(SRAMCCM);		//初始化CCM内存池

    //软件初始化
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
	LOG_DEBUG("Hello World!");
#if 0	
	POINT_COLOR = RED; 		
	LCD_ShowString(30,30,200,16,16,"Explorer STM32F4");
	LCD_ShowString(30,50,200,16,16,"Ethernet lwIP Test");
	LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,90,200,16,16,"2014/8/15"); 
	TIM3_Int_Init(999,839); //100hz的频率
	while(lwip_comm_init()) //lwip初始化
	{
		LCD_ShowString(30,110,200,20,16,"LWIP Init Falied!");
		delay_ms(1200);
		LCD_Fill(30,110,230,130,WHITE); //清除显示
		LCD_ShowString(30,110,200,16,16,"Retrying...");  
	}
	LCD_ShowString(30,110,200,20,16,"LWIP Init Success!");
 	LCD_ShowString(30,130,200,16,16,"DHCP IP configing...");  //等待DHCP获取 
#if LWIP_DHCP   //使用DHCP
	while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//等待DHCP获取成功/超时溢出
	{
		lwip_periodic_handle();	//LWIP内核需要定时处理的函数
	}
#endif
	show_address(lwipdev.dhcpstatus);	//显示地址信息
	while(1)
	{
		lwip_periodic_handle();	//LWIP内核需要定时处理的函数
	}
#else    
	//创建任务函数
	card_setup();
	    
    vTaskStartScheduler();          //开启任务调度
#endif
}



