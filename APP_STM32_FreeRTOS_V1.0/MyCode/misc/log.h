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
#include "control.h"

extern UI8_T log_level;
extern void print_buf(unsigned char * pBuf,  int iLen);


#define LOGGER_ON           1
#define LOGGER_OFF          0


//����log���ܿ�����
#define VERBOSE_LOG_EN      LOGGER_ON
#define DEBUG_LOG_EN        LOGGER_ON
#define INFO_LOG_EN         LOGGER_ON
#define WARN_LOG_EN         LOGGER_ON
#define ERROR_LOG_EN        LOGGER_ON
#define ASSERT_LOG_EN       LOGGER_ON


//��ӡ�ȼ����ȼ�Խ�ߣ�����ԽС��log_levelΪ0ʱ��ֻ��VER��ӡ������ʾ��log_levelΪ5ʱ�����д�ӡ��������ʾ
#define LEVEL_VERBOSE       5       //��ϸ
#define LEVEL_DEBUG         4       //����
#define LEVEL_INFO          3       //��Ϣ
#define LEVEL_WARN          2       //����
#define LEVEL_ERROR         1       //����
#define LEVEL_ASSERT        0       //����


//�ļ���ַȫ·����ֻ��ʾ�ļ�������
#if 1
#define filename(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define filename(x) (x)
#endif


//���������������л�ʱ��printf��ӡ����ִ�ӡ���������
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
