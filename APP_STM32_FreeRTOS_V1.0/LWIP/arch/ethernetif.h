#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__
#include "lwip/err.h"
#include "lwip/netif.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ethernetif ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/8/15
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   


//����������
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
