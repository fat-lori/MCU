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
    //Ӳ����ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
    delay_init(168);		//��ʼ����ʱ����
    uart_init(115200);     	//��ʼ������
    LED_Init();		        //��ʼ��LED�˿�
    KEY_Init();  			//��ʼ������
    LCD_Init(); 			//��ʼ��LCD
    TIM3_Int_Init(999,839); //��ʼ����ʱ��3��100Hz��Ƶ��
    LCD_ShowString(10,10,200,20,16,"HardWare Init Successful!");
    FSMC_SRAM_Init();			//��ʼ���ⲿSRAM  
    printf("HardWare Init Successful!");
    
    //mymalloc��ʼ��
    my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
    my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��

    //�����ʼ��
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
    lock_init();
    LOG_DEBUG("SofeWare Init Successful!");

    POINT_COLOR = RED; 		
    LCD_ShowString(30,30,200,16,16,"Explorer STM32F4");
    LCD_ShowString(30,90,200,16,16,"2014/8/15"); 


    //����������
    card_setup();

    //�����������
    vTaskStartScheduler();

    return 0;
}



