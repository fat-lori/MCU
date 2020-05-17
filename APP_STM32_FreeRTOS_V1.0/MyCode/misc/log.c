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




