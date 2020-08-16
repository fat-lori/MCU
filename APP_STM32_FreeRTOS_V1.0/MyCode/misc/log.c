/***********************************************************************************
 * �� �� ��   : log.c
 * �� �� ��   : ����
 * ��������   : 2020��5��12��
 * �ļ�����   : ���log��־ʵ�ֺ���
 * ��Ȩ˵��   : Copyright (c) 2008-2020   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
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


void print_buf(unsigned char * pBuf,  int iLen)
{
    UI8_T i = 0;

    if(iLen<=0)
   	    return;
    
    for (i=0; i<iLen; i++)
    {
        if (i%16 == 0)
            printf("\r\n %.2d \t:(HEX)",i);
        printf("%d ",pBuf[i]);
    
    }
    printf("\r\n");
}





