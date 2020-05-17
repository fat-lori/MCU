/***********************************************************************************
 * 文 件 名   : control.h
 * 负 责 人   : 罗瑞
 * 创建日期   : 2019年12月18日
 * 文件描述   : control.c 的头文件
 * 版权说明   : Copyright (c) 2008-2019   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/

#ifndef __CONTROL_H__
#define __CONTROL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "queue.h"

typedef enum {
	QUEUE_SRC_TEST      = 0,
	QUEUE_SRC_MAX,
}QUEUE_SRC_T;



typedef enum {

	LOCK_SRC_CPLD_I2C	= 0,
	LOCK_SRC_I2C		= 1,
	LOCK_SRC_SPI		= 2,
	LOCK_SRC_ELOG		= 3,	
	LOCK_SRC_UART0		= 4,
	LOCK_SRC_UART1		= 5,
	LOCK_SRC_UART2		= 6,
	LOCK_SRC_MAX,
}LOCK_SRC_T;



extern int init_queue(QUEUE_SRC_T queue_src,u16 queue_len,u16 item_len);
extern QueueHandle_t get_queue(QUEUE_SRC_T queue_src);
extern int lock_init(void);
extern int lock_src(LOCK_SRC_T src,u32 timeout);
extern int unlock_src(LOCK_SRC_T src);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CONTROL_H__ */
