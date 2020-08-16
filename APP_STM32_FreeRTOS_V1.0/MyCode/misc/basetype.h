/***********************************************************************************
 * �� �� ��   : basetype.h
 * �� �� ��   : ����
 * ��������   : 2020��5��12��
 * �ļ�����   : basetype.c ��ͷ�ļ�
 * ��Ȩ˵��   : Copyright (c) 2008-2020   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
***********************************************************************************/

#ifndef __BASETYPE_H__
#define __BASETYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


typedef unsigned char       UI8_T;
typedef unsigned short      UI16_T;
typedef unsigned int        UI32_T;
typedef unsigned long long  UI64_T;

typedef signed char         I8_T;
typedef signed short        I16_T;
typedef signed long         I32_T;


typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int    DWORD;


#define FALSE       0
#define TRUE        1

#define RUN_SUCCESS     0
#define RUN_ERR         1
#define RUN_PRGRAM_ERR  2


#define checkbit8(var,bit)   (var & ((UI8_T)0x01 << (bit)))        //������λΪ1������1; ���λΪ0������0
#define setbit8(var,bit)     (var |= ((UI8_T)0x01 << (bit)))       //����Ӧλ����Ϊ1
#define clrbit8(var,bit)     (var &= (~((UI8_T)0x01 << (bit))))    //����Ӧλ����Ϊ0
#define checkbit16(var,bit)  (var & ((UI16_T)0x01 << (bit)))       //������λΪ1������1; ���λΪ0������0
#define setbit16(var,bit)    (var |= ((UI16_T)0x01 << (bit)))      //����Ӧλ����Ϊ1
#define clrbit16(var,bit)    (var &= (~((UI16_T)0x01 << (bit))))   //����Ӧλ����Ϊ0
#define checkbit32(var,bit)  (var & ((UI32_T)0x01 << (bit)))       //������λΪ1������1; ���λΪ0������0
#define setbit32(var,bit)    (var |= ((UI32_T)0x01 << (bit)))      //����Ӧλ����Ϊ1
#define clrbit32(var,bit)    (var &= (~((UI32_T)0x01 << (bit))))   //����Ӧλ����Ϊ0

#define ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))          //��������ĸ���


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BASETYPE_H__ */
