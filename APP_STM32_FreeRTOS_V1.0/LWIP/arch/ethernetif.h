#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__
#include "lwip/err.h"
#include "lwip/netif.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ethernetif 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/8/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//*******************************************************************************
//修改信息
//无
////////////////////////////////////////////////////////////////////////////////// 	   


//网卡的名字
#define IFNAME0 'e'
#define IFNAME1 'n'

#define MAC0    0X0A
#define MAC1    0X0B
#define MAC2    0X0C
#define MAC3    0X0D
#define MAC4    0X0E
#define MAC5    0X0F


/*Static IP*/
#define IP_ADDR0                    192
#define IP_ADDR1                    168
#define IP_ADDR2                      1
#define IP_ADDR3                    102

/*NETMASK*/
#define NETMASK_ADDR0               255
#define NETMASK_ADDR1               255
#define NETMASK_ADDR2               255
#define NETMASK_ADDR3                 0

/*Gateway Address*/
#define GW_ADDR0                    192
#define GW_ADDR1                    168
#define GW_ADDR2                      1
#define GW_ADDR3                      1




err_t ethernetif_init(struct netif *netif);
err_t ethernetif_input(struct netif *netif);
#endif
