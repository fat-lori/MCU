#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

typedef enum{
	UART_INDX_1		= 0,
	UART_INDX_2		= 1,
	UART_INDX_3		= 2,
	UART_INDX_MAX
}UART_INDX_E;

#define UART_READ_SUCCESS  	0
#define UART_READ_EMPTY  	1
#define UART_READ_TIMEOUT  	2
#define UART_READ_LENERR  	3
#define UART_READ_CRCERR  	4
#define UART_PARAM_ERR  	5
#define UART_READ_BUSY  	6
#define UART_SEND_ERR  		7




extern int fputc(int ch, FILE *f);
extern u8 IfUartGetByte(UART_INDX_E uart_num);
extern void _sys_exit(int x);
extern u16 uart2_get_byte(void);
extern u8 uart2_if_recv(void);
extern void uart2_send_byte(const u8 sent_data);
extern int uart2_send_recv(char *send,u16 send_len,char *recv,u16 *recv_len,u16 timeout_ms);
extern u16 UartGetByte(UART_INDX_E uart_num);
extern void UARTSend(UART_INDX_E uart_num, const u8 *pucBuffer, unsigned long ulCount);
extern void UartSendByte(UART_INDX_E uart_num, const u8 sent_data);
extern void UartSendStr(UART_INDX_E uart_num, const u8 *p_data);
extern void uart_init(u32 bound);
extern int uart_send_recv(UART_INDX_E uart_num,char *send,u16 send_len,char *recv,u16 *recv_len,u16 recv_len_max,u16 timeout_ms);
extern void uart3_send_str(const u8 *sent_data);

#endif


