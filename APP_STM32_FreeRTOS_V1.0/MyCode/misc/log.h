/***********************************************************************************
 * �� �� ��   : log.h
 * �� �� ��   : ����
 * ��������   : 2020��5��12��
 * �ļ�����   : log.c ��ͷ�ļ�
 * ��Ȩ˵��   : Copyright (c) 2008-2020   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
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

extern UI8_T log_level;

#define LOGGER_ON           1
#define LOGGER_OFF          0

//����log���ܿ�����
#define VERBOSE_LOG_EN      LOGGER_ON
#define DEBUG_LOG_EN        LOGGER_ON
#define INFO_LOG_EN         LOGGER_ON
#define WARN_LOG_EN         LOGGER_ON
#define ERROR_LOG_EN        LOGGER_ON
#define ASSERT_LOG_EN       LOGGER_ON





#define LEVEL_VERBOSE       5
#define LEVEL_DEBUG         4
#define LEVEL_INFO          5
#define LEVEL_WARN          2
#define LEVEL_ERROR         1
#define LEVEL_ASSERT        0





#define filename(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x

#if VERBOSE_LOG_EN == LOGGER_ON
#define LOG_VER(format, ...)  if(log_level>=LEVEL_VERBOSE)\
                                printf("\r\n\033[34m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_VER(format, ...)
#endif


#if DEBUG_LOG_EN == LOGGER_ON
#define LOG_DEBUG(format, ...)  if(log_level>=LEVEL_DEBUG)\
                                printf("\r\n\033[32m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#endif


#if INFO_LOG_EN == LOGGER_ON
#define LOG_INFO(format, ...)  if(log_level>=LEVEL_INFO)\
                                printf("\r\n\033[36m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif


#if WARN_LOG_EN == LOGGER_ON
#define LOG_WARN(format, ...)  if(log_level>=LEVEL_WARN)\
                                printf("\r\n\033[33m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_WARN(format, ...)
#endif


#if ERROR_LOG_EN == LOGGER_ON
#define LOG_ERROR(format, ...)  if(log_level>=LEVEL_ERROR)\
                                printf("\r\n\033[31m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_ERROR(format, ...)
#endif


#if ASSERT_LOG_EN == LOGGER_ON
#define LOG_ASSERT(format, ...)  if(log_level>=LEVEL_ASSERT)\
                                printf("\r\n\033[35m [%s]\t %s:%d(%s) --> "format" \033[0m", LOG_TAG, filename(__FILE__), __LINE__, __func__, ##__VA_ARGS__)
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
