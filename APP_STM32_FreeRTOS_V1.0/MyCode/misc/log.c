/***********************************************************************************
 * 文 件 名   : log.c
 * 负 责 人   : 罗瑞
 * 创建日期   : 2020年5月12日
 * 文件描述   : 输出log日志实现函数
 * 版权说明   : Copyright (c) 2008-2020   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "basetype.h"



#define LOG_TAG     "log"
#include "log.h"




UI8_T log_level = 4;




void set_log_level(UI8_T level)
{
    LOG_DEBUG("set log level to %d", level);
    log_level = level;
    
}




