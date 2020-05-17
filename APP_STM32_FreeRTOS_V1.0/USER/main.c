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
    //Ӳ����ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED�˿�
	KEY_Init();  			//������ʼ��
	LCD_Init(); 			//LCD��ʼ��
	LCD_ShowString(10,10,200,20,16,"HardWare Init Successful!");
	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM  
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��

    //�����ʼ��
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
	LOG_DEBUG("Hello World!");
#if 0	
	POINT_COLOR = RED; 		
	LCD_ShowString(30,30,200,16,16,"Explorer STM32F4");
	LCD_ShowString(30,50,200,16,16,"Ethernet lwIP Test");
	LCD_ShowString(30,70,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,90,200,16,16,"2014/8/15"); 
	TIM3_Int_Init(999,839); //100hz��Ƶ��
	while(lwip_comm_init()) //lwip��ʼ��
	{
		LCD_ShowString(30,110,200,20,16,"LWIP Init Falied!");
		delay_ms(1200);
		LCD_Fill(30,110,230,130,WHITE); //�����ʾ
		LCD_ShowString(30,110,200,16,16,"Retrying...");  
	}
	LCD_ShowString(30,110,200,20,16,"LWIP Init Success!");
 	LCD_ShowString(30,130,200,16,16,"DHCP IP configing...");  //�ȴ�DHCP��ȡ 
#if LWIP_DHCP   //ʹ��DHCP
	while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//�ȴ�DHCP��ȡ�ɹ�/��ʱ���
	{
		lwip_periodic_handle();	//LWIP�ں���Ҫ��ʱ����ĺ���
	}
#endif
	show_address(lwipdev.dhcpstatus);	//��ʾ��ַ��Ϣ
	while(1)
	{
		lwip_periodic_handle();	//LWIP�ں���Ҫ��ʱ����ĺ���
	}
#else    
	//����������
	card_setup();
	    
    vTaskStartScheduler();          //�����������
#endif
}



