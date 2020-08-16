/***********************************************************************************
 * 文 件 名   : control.c
 * 负 责 人   : 罗瑞
 * 创建日期   : 2019年12月18日
 * 文件描述   : 队列、信号量等RTOS控制
 * 版权说明   : Copyright (c) 2008-2019   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/
#include "control.h"
#include "task.h"
#include "semphr.h"



static QueueHandle_t Queue_Handle[QUEUE_SRC_MAX] = {0};
static SemaphoreHandle_t mutex_lock[LOCK_SRC_MAX] = {0};



int init_queue(QUEUE_SRC_T queue_src,u16 queue_len,u16 item_len)
{
	
	Queue_Handle[queue_src] = xQueueCreate(queue_len,item_len);

	if(Queue_Handle[queue_src] == NULL)
		return -1;
	else
		return 0;
}

QueueHandle_t get_queue(QUEUE_SRC_T queue_src)
{
	return Queue_Handle[queue_src];
}


int lock_init(void)
{
	u8 i = 0;
	
	for(i = 0; i < LOCK_SRC_MAX; i++)
	{
		if(mutex_lock[i] == NULL)
		{
			mutex_lock[i] = xSemaphoreCreateMutex();
			if(mutex_lock[i] == NULL)
			{
			//	print("\r\nCreat muxtex failed:%d\r\n",i);
				return -1;
			}
		}
	}
	
	return 0;
}

int lock_src(LOCK_SRC_T src, u32 timeout)
{
	return xSemaphoreTake(mutex_lock[src],timeout);
}

int unlock_src(LOCK_SRC_T src)
{
	return xSemaphoreGive(mutex_lock[src]);
}

