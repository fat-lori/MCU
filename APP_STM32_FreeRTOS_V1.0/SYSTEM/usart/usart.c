#include "sys.h"
#include "usart.h"	
#include "control.h"
#include "delay.h"
#include "basetype.h"
#include "cli.h"


#define EN_UART1    0
#define EN_UART2    0
#define EN_UART3    1

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	USART3->DR = (u8) ch;      
	return ch;
}
/***************************************************************************************/
 

#define RX_BUFFER_SIZE		512 
#define RX_BUFFER_MAXSIZE	1200 

static unsigned char uart_rx_buffer[UART_INDX_MAX][RX_BUFFER_MAXSIZE]; 			//存储串口接收数据
static volatile u16 uart_rx_wr_index[UART_INDX_MAX];							//记录已经写入uart_rx_buffer数组的位数
static volatile u16 uart_rx_rd_index[UART_INDX_MAX];							//记录已经从uart_rx_buffer数组中读取的位数
static USART_TypeDef *uart_base[UART_INDX_MAX] = {USART1,USART2,USART3};


/*****************************************************************************
 * 函 数 名  : uart_init
 * 负 责 人  : 罗瑞
 * 创建日期  : 2019年12月17日
 * 函数功能  : UART1初始化
 * 输入参数  : u32 bound  波特率
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 
*****************************************************************************/
void uart_init(u32 bound){
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
#if EN_UART1
    /************uart1 init*****************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_RXNE);	//清除接收中断标志位
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
#endif

#if EN_UART2
    /************uart2 init*****************/	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口2对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);	//清除接收中断标志位
    
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
#endif

#if EN_UART3
    /************uart3 init*****************/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	
	//USART3端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
	USART_Cmd(USART3, ENABLE);  //使能串口3 
	
	USART_ClearFlag(USART3, USART_FLAG_RXNE);	//清除接收中断标志位
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口3中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
#endif
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //判断是否是接收中断
	{
		data =USART_ReceiveData(USART1);//(USART1->DR);	//读接收寄存器，系统自动清除接收中断标志位
		
		uart_rx_buffer[UART_INDX_1][uart_rx_wr_index[UART_INDX_1]]=data;
		if (++uart_rx_wr_index[UART_INDX_1] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_1] = 0;
		cli_timeOut = 240;
	} 
} 
	
void USART2_IRQHandler(void)                	//串口3中断服务程序
{
	u8 data;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //判断是否是接收中断
	{
		data =USART_ReceiveData(USART2);//(USART1->DR);	//读接收寄存器，系统自动清除接收中断标志位
		
		uart_rx_buffer[UART_INDX_2][uart_rx_wr_index[UART_INDX_2]]=data;
		if (++uart_rx_wr_index[UART_INDX_2] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_2] = 0;
		cli_timeOut = 240;
	} 
} 

void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //判断是否是接收中断
	{
		data =USART_ReceiveData(USART3);//(USART1->DR);	//读接收寄存器，系统自动清除接收中断标志位
		
		uart_rx_buffer[UART_INDX_3][uart_rx_wr_index[UART_INDX_3]]=data;
		if (++uart_rx_wr_index[UART_INDX_3] >= RX_BUFFER_MAXSIZE) 
		   uart_rx_wr_index[UART_INDX_3] = 0;
		cli_timeOut = 240;
	} 
}


//发送一串字符串
void UartSendStr(UART_INDX_E uart_num, const u8 *p_data)
{
	while (*p_data != '\0')
	{
		UartSendByte(uart_num,*p_data++);
	}
		return;
}

//发送一串数据 
void UARTSend(UART_INDX_E uart_num, const u8 *pucBuffer, unsigned long ulCount)
{

    while(ulCount--)
    {
        UartSendByte(uart_num, *pucBuffer++);
    }
}
//发送单个数据
void UartSendByte(UART_INDX_E uart_num, const u8 sent_data) 
{ 
	while(USART_GetFlagStatus(uart_base[uart_num], USART_FLAG_TC) == RESET);
	USART_SendData(uart_base[uart_num], sent_data);
}
//判断串口是否还有数据输入
u8 IfUartGetByte(UART_INDX_E uart_num) 
{ 
  if (uart_rx_rd_index[uart_num] == uart_rx_wr_index[uart_num])
    return (0); 
  else
    return (1); 
}
//获取串口中输入的数据
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





