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
    //Ӳ����ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
    delay_init(168);            //��ʼ����ʱ����
    uart_init(115200);          //��ʼ������
    LED_Init();                 //��ʼ��LED�˿�
    KEY_Init();                 //��ʼ������
    TIM3_Int_Init(999,839);     //��ʼ����ʱ��3��100Hz��Ƶ��
    FSMC_SRAM_Init();           //��ʼ���ⲿSRAM
    LAN8720_Init();             //����Ӳ����ʼ��
    LCD_Init();                 //��ʼ��LCD
    printf("\r\n HardWare Init Successful!");



    //�����ʼ��
    //init_malloc();              //��ʼ���ڴ��
    init_queue(QUEUE_SRC_TEST, 16, sizeof(int));
    lock_init();
    LOG_INFO("SofeWare Init Successful!");



    //����������
    card_setup();


    //�����������
    vTaskStartScheduler();

    return 0;
}



