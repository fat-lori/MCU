/***********************************************************************************
 * 文 件 名   : basetype.h
 * 负 责 人   : 罗瑞
 * 创建日期   : 2020年5月12日
 * 文件描述   : basetype.c 的头文件
 * 版权说明   : Copyright (c) 2008-2020   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
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


#define checkbit8(var,bit)   (var & ((UI8_T)0x01 << (bit)))        //如果检测位为1，返回1; 检测位为0，返回0
#define setbit8(var,bit)     (var |= ((UI8_T)0x01 << (bit)))       //将对应位设置为1
#define clrbit8(var,bit)     (var &= (~((UI8_T)0x01 << (bit))))    //将对应位设置为0
#define checkbit16(var,bit)  (var & ((UI16_T)0x01 << (bit)))       //如果检测位为1，返回1; 检测位为0，返回0
#define setbit16(var,bit)    (var |= ((UI16_T)0x01 << (bit)))      //将对应位设置为1
#define clrbit16(var,bit)    (var &= (~((UI16_T)0x01 << (bit))))   //将对应位设置为0
#define checkbit32(var,bit)  (var & ((UI32_T)0x01 << (bit)))       //如果检测位为1，返回1; 检测位为0，返回0
#define setbit32(var,bit)    (var |= ((UI32_T)0x01 << (bit)))      //将对应位设置为1
#define clrbit32(var,bit)    (var &= (~((UI32_T)0x01 << (bit))))   //将对应位设置为0

#define ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))          //计算数组的个数


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BASETYPE_H__ */
