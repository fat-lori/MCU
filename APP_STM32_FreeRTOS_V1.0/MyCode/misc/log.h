/***********************************************************************************
 * 文 件 名   : log.h
 * 负 责 人   : 罗瑞
 * 创建日期   : 2020年5月12日
 * 文件描述   : log.c 的头文件
 * 版权说明   : Copyright (c) 2008-2020   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/

#ifndef __LOG_H__
#define __LOG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <string.h>
#include "basetype.h"
#include "control.h"

extern UI8_T log_level;
extern void print_buf(unsigned char * pBuf,  int iLen);


#define LOGGER_ON           1
#define LOGGER_OFF          0


//所有log的总开开关
#define VERBOSE_LOG_EN      LOGGER_ON
#define DEBUG_LOG_EN        LOGGER_ON
#define INFO_LOG_EN         LOGGER_ON
#define WARN_LOG_EN         LOGGER_ON
#define ERROR_LOG_EN        LOGGER_ON
#define ASSERT_LOG_EN       LOGGER_ON


//打印等级，等级越高，数字越小，log_level为0时，只有VER打印可以显示；log_level为5时，所有打印都可以显示
#define LEVEL_VERBOSE       5       //详细
#define LEVEL_DEBUG         4       //调试
#define LEVEL_INFO          3       //信息
#define LEVEL_WARN          2       //警告
#define LEVEL_ERROR         1       //错误
#define LEVEL_ASSERT        0       //断言


//文件地址全路径和只显示文件名开关
#if 1
#define filename(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define filename(x) (x)
#endif


//若不加锁，任务切换时，printf打印会出现打印错误的问题
#if VERBOSE_LOG_EN == LOGGER_ON
#define LOG_VER(format, ...)        do{\
                                        if(LEVEL_VERBOSE <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[34m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_VER(format, ...)
#endif


#if DEBUG_LOG_EN == LOGGER_ON
#define LOG_DEBUG(format, ...)      do{\
                                        if(LEVEL_DEBUG <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[32m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_DEBUG(format, ...)
#endif


#if INFO_LOG_EN == LOGGER_ON
#define LOG_INFO(format, ...)   do{\
                                        if(LEVEL_INFO <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[32m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_INFO(format, ...)
#endif


#if WARN_LOG_EN == LOGGER_ON
#define LOG_WARN(format, ...)       do{\
                                        if(LEVEL_WARN <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[32m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_WARN(format, ...)
#endif


#if ERROR_LOG_EN == LOGGER_ON
#define LOG_ERR(format, ...)        do{\
                                        if(LEVEL_ERROR <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[32m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_ERR(format, ...)
#endif


#if ASSERT_LOG_EN == LOGGER_ON
#define LOG_ASSERT(format, ...)     do{\
                                        if(LEVEL_ASSERT <= log_level){\
                                            lock_src(LOCK_SRC_PRINTF, portMAX_DELAY);\
                                            printf("\r\n\033[32m [%-5.5s]    %-14s:%-4d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);\
                                            unlock_src(LOCK_SRC_PRINTF);\
                                        }\
                                    }while(0)
#else
#define LOG_ASSERT(format, ...)
#endif



extern void set_log_level(UI8_T level);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LOG_H__ */
