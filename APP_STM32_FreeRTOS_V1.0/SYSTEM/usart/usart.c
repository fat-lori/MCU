#include "sys.h"
#include "usart.h"	
#include "control.h"
#include "delay.h"
#include "basetype.h"
#include "cli.h"


#define EN_UART1    0
#define EN_UART2    0
#define EN_UART3    1

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
	USART3->DR = (u8) ch;      
	return ch;
}
/***************************************************************************************/
 

#define RX_BUFFER_SIZE		512 
#define RX_BUFFER_MAXSIZE	1200 

static unsigned char uart_rx_buffer[UART_INDX_MAX][RX_BUFFER_MAXSIZE]; 			//�洢���ڽ�������
static volatile u16 uart_rx_wr_index[UART_INDX_MAX];							//��¼�Ѿ�д��uart_rx_buffer�����λ��
static volatile u16 uart_rx_rd_index[UART_INDX_MAX];							//��¼�Ѿ���uart_rx_buffer�����ж�ȡ��λ��
static USART_TypeDef *uart_base[UART_INDX_MAX] = {USART1,USART2,USART3};


/*****************************************************************************
 * �� �� ��  : uart_init
 * �� �� ��  : ����
 * ��������  : 2019��12��17��
 * ��������  : UART1��ʼ��
 * �������  : u32 bound  ������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 
*****************************************************************************/
void uart_init(u32 bound){
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
#if EN_UART1
    /************uart1 init*****************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_RXNE);	//��������жϱ�־λ
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#endif

#if EN_UART2
    /************uart2 init*****************/	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);	//��������жϱ�־λ
    
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif

#if EN_UART3
    /************uart3 init*****************/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	
	//USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3 
	
	USART_ClearFlag(USART3, USART_FLAG_RXNE);	//��������жϱ�־λ
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�ж��Ƿ��ǽ����ж�
	{
		data =USART_ReceiveData(USART1);//(USART1->DR);	//�����ռĴ�����ϵͳ�Զ���������жϱ�־λ
		
		uart_rx_buffer[UART_INDX_1][uart_rx_wr_index[UART_INDX_1]]=data;
		if (++uart_rx_wr_index[UART_INDX_1] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_1] = 0;
		cli_timeOut = 240;
	} 
} 
	
void USART2_IRQHandler(void)                	//����3�жϷ������
{
	u8 data;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�ж��Ƿ��ǽ����ж�
	{
		data =USART_ReceiveData(USART2);//(USART1->DR);	//�����ռĴ�����ϵͳ�Զ���������жϱ�־λ
		
		uart_rx_buffer[UART_INDX_2][uart_rx_wr_index[UART_INDX_2]]=data;
		if (++uart_rx_wr_index[UART_INDX_2] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_2] = 0;
		cli_timeOut = 240;
	} 
} 

void USART3_IRQHandler(void)                	//����3�жϷ������
{
	u8 data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�ж��Ƿ��ǽ����ж�
	{
		data =USART_ReceiveData(USART3);//(USART1->DR);	//�����ռĴ�����ϵͳ�Զ���������жϱ�־λ
		
		uart_rx_buffer[UART_INDX_3][uart_rx_wr_index[UART_INDX_3]]=data;
		if (++uart_rx_wr_index[UART_INDX_3] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_3] = 0;
		cli_timeOut = 240;
	} 
}


//����һ���ַ���
void UartSendStr(UART_INDX_E uart_num, const u8 *p_data)
{
	while (*p_data != '\0')
	{
		UartSendByte(uart_num,*p_data++);
	}
		return;
}

//����һ������ 
void UARTSend(UART_INDX_E uart_num, const u8 *pucBuffer, unsigned long ulCount)
{

    while(ulCount--)
    {
        UartSendByte(uart_num, *pucBuffer++);
    }
}
//���͵�������
void UartSendByte(UART_INDX_E uart_num, const u8 sent_data) 
{ 
	while(USART_GetFlagStatus(uart_base[uart_num], USART_FLAG_TC) == RESET);
	USART_SendData(uart_base[uart_num], sent_data);
}
//�жϴ����Ƿ�����������
u8 IfUartGetByte(UART_INDX_E uart_num) 
{ 
  if (uart_rx_rd_index[uart_num] == uart_rx_wr_index[uart_num])
    return (0); 
  else
    return (1); 
}
//��ȡ���������������
u16 UartGetByte(UART_INDX_E uart_num) 
{ 
	char data; 
	
	if (uart_rx_rd_index[uart_num] == uart_rx_wr_index[uart_num])
		return (0x8000); 
	data=uart_rx_buffer[uart_num][uart_rx_rd_index[uart_num]]; 
	if (++uart_rx_rd_index[uart_num] >= RX_BUFFER_MAXSIZE) 
		uart_rx_rd_index[uart_num] = 0; 

	return data; 
} 



 

/******************************************************************************/
/*						  Uart send function 					  */
/******************************************************************************/





int uart_send_recv(UART_INDX_E uart_num,char *send,u16 send_len,char *recv,u16 *recv_len,u16 recv_len_max,u16 timeout_ms)
{
	u16 count = 0, i = 0;
	int iRet = UART_READ_SUCCESS;
	u16 ui16_data = 0;
	if(uart_num == UART_INDX_1)
		lock_src(LOCK_SRC_UART0,portMAX_DELAY);
	else if(uart_num == UART_INDX_2)
		lock_src(LOCK_SRC_UART1,portMAX_DELAY);
	else if(uart_num == UART_INDX_3)
		lock_src(LOCK_SRC_UART2,portMAX_DELAY);
	else
		printf("lock uart number error!");

	if((send == NULL) || (recv == NULL) || (recv_len == NULL))
	{
		iRet = UART_PARAM_ERR;
		goto RET;
	}

	if(send_len)
	{
		while(IfUartGetByte(uart_num) != 0)
		{
			UartGetByte(uart_num);
			if(count++ > 20)
			{
				iRet = UART_READ_BUSY;
				goto RET;
			}
			msleep(5);
		}

		UARTSend(uart_num,(u8*) send,send_len);
	}
	count = 0;
	while(IfUartGetByte(uart_num) == 0)
	{
		if(count++ >= (timeout_ms/5))
		{
			iRet = UART_READ_EMPTY;
			goto RET;
		}
		msleep(5);
	}

	count = 0;
	i = 0;
	while(i < recv_len_max)
	{
		if(IfUartGetByte(uart_num) == 0)
		{
			if(count++ >= 10)
				break;
			msleep(5);
		}
		else
		{
			count = 0;		
			ui16_data = UartGetByte(uart_num);
			if(ui16_data <= 0xff)
				recv[i++] = ui16_data;
			
		}
	}	
	*recv_len = i;
	
RET:
	if(uart_num == UART_INDX_1)
		unlock_src(LOCK_SRC_UART0);
	else if(uart_num == UART_INDX_2)
		unlock_src(LOCK_SRC_UART1);
	else if(uart_num == UART_INDX_3)
		unlock_src(LOCK_SRC_UART2);
	else
		printf("lock uart number error!");
	
	return iRet;

}


int uart2_send_recv(char *send,u16 send_len,char *recv,u16 *recv_len,u16 timeout_ms)
{
	return uart_send_recv(UART_INDX_2 ,send,send_len, recv, recv_len, 1024, timeout_ms);
}


void uart2_send_byte(const u8 sent_data)
{
	UartSendByte(UART_INDX_2, sent_data);
}


u8 uart2_if_recv(void) 
{ 
	return IfUartGetByte(UART_INDX_2);
}


u16 uart2_get_byte(void) 
{
	return UartGetByte(UART_INDX_2);
}

void uart3_send_str(const u8 *sent_data)
{
	UartSendStr(UART_INDX_3, sent_data);
}





