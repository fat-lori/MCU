#include "arch/ethernetif.h" 
#include "lan8720.h"  
#include "netif/etharp.h"  
#include "string.h"  


#include "lwip/ip_addr.h"
#include "lwip/ip4_addr.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "log.h"
#define LOG_TAG     "eth"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ethernetif.c ����	   
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



/* Variables Initialization */
struct netif gnetif;
ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gw;


void TCPIP_Init(void)
{
    tcpip_init(NULL, NULL);

    if(ETH_Mem_Malloc())
    {
        LOG_ERR("\r\n malloc fail");
        return;       //�ڴ�����ʧ��
    }

    struct netif *Netif_Init_Flag;		//����netif_add()����ʱ�ķ���ֵ,�����ж������ʼ���Ƿ�ɹ�
    /* IP addresses initialization */
    /* USER CODE BEGIN 0 */
#if LWIP_DHCP
    ip_addr_set_zero_ip4(&ipaddr);
    ip_addr_set_zero_ip4(&netmask);
    ip_addr_set_zero_ip4(&gw);
#else
    IP4_ADDR(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
    IP4_ADDR(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
    IP4_ADDR(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
#endif /* USE_DHCP */
    /* USER CODE END 0 */
    /* Initilialize the LwIP stack without RTOS */
    /* add the network interface (IPv4/IPv6) without RTOS */
    Netif_Init_Flag = netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
    if (Netif_Init_Flag == NULL)
        LOG_ERR("\r\n netif init fail");
    else 
        LOG_DEBUG("\r\n netif init successful");
    /* Registers the default network interface */
    netif_set_default(&gnetif);

    if (netif_is_link_up(&gnetif))
    {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
    printf("\r\n netif startup");
    }
    else
    {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
    printf("\r\n netif down");
    }

#if LWIP_DHCP	   			//��ʹ����DHCP
    int err;
    /*  Creates a new DHCP client for this interface on the first call.
    Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
    the predefined regular intervals after starting the client.
    You can peek in the netif->dhcp struct for the actual DHCP status.*/

    printf("\r\n �����̽�ʹ��DHCP��̬����IP��ַ,�������Ҫ����lwipopts.h�н�LWIP_DHCP����Ϊ0");

    err = dhcp_start(&gnetif);      //����dhcp
    if(err == ERR_OK)
    printf("\r\n lwip dhcp init success...");
    else
    printf("\r\n lwip dhcp init fail...");
    while(ip_addr_cmp(&(gnetif.ip_addr),&ipaddr))   //�ȴ�dhcp�����ip��Ч
    {
    vTaskDelay(1);
    } 
#endif
    printf("\r\n ����IP��ַ��:%d.%d.%d.%d",      ((gnetif.ip_addr.addr)&0x000000ff),       \
                                            (((gnetif.ip_addr.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.ip_addr.addr)&0x00ff0000)>>16), \
                                            ((gnetif.ip_addr.addr)&0xff000000)>>24);
    printf("\r\n ����MASK��ַ��:%d.%d.%d.%d",      ((gnetif.netmask.addr)&0x000000ff),       \
                                            (((gnetif.netmask.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.netmask.addr)&0x00ff0000)>>16), \
                                            ((gnetif.netmask.addr)&0xff000000)>>24);
    printf("\r\n ����GW��ַ��:%d.%d.%d.%d",      ((gnetif.gw.addr)&0x000000ff),       \
                                            (((gnetif.gw.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.gw.addr)&0x00ff0000)>>16), \
                                            ((gnetif.gw.addr)&0xff000000)>>24);
}



SemaphoreHandle_t BinarySemaphoreMacRx = NULL;

 //������̫���жϵ���
void lwip_pkt_handle(void)
{
    BaseType_t pxHigherPriorityTaskWoken;
	xSemaphoreGiveFromISR(BinarySemaphoreMacRx, &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
}


//�������handle����������жϾ͵��ôκ��������������ݴ�����LWIP�ں���
void polling_mac_rx(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(BinarySemaphoreMacRx, portMAX_DELAY);
        while(ETH_GetRxPktSize(DMARxDescToGet)!=0)  //����Ƿ��յ����ݰ�
        {
            ethernetif_input(&gnetif);
        }
        
	}
}


 
//��ethernetif_init()�������ڳ�ʼ��Ӳ��
//netif:�����ṹ��ָ�� 
//����ֵ:ERR_OK,����
//       ����,ʧ��
static err_t low_level_init(struct netif *netif)
{
#ifdef CHECKSUM_BY_HARDWARE
	int i; 
#endif 
	netif->hwaddr_len = ETHARP_HWADDR_LEN; //����MAC��ַ����,Ϊ6���ֽ�
	//��ʼ��MAC��ַ,����ʲô��ַ���û��Լ�����,���ǲ����������������豸MAC��ַ�ظ�
	netif->hwaddr[0]=MAC0; 
	netif->hwaddr[1]=MAC1; 
	netif->hwaddr[2]=MAC2;
	netif->hwaddr[3]=MAC3;
	netif->hwaddr[4]=MAC4;
	netif->hwaddr[5]=MAC5;
	netif->mtu=1500; //��������䵥Ԫ,����������㲥��ARP����
	//���Ҹ�����������Ӳ����·����
	netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;
	
	ETH_MACAddressConfig(ETH_MAC_Address0, netif->hwaddr); //��STM32F4��MAC��ַ�Ĵ�����д��MAC��ַ
	ETH_DMATxDescChainInit(DMATxDscrTab, Tx_Buff, ETH_TXBUFNB);
	ETH_DMARxDescChainInit(DMARxDscrTab, Rx_Buff, ETH_RXBUFNB);

    //���������ź�����������MAC�жϴ���
    BinarySemaphoreMacRx = xSemaphoreCreateBinary();
    if (BinarySemaphoreMacRx == NULL)
        printf("\r\n create MAC RX semaphore fail");

    //�������񣬸����жϲ�ͣ��ȡMAC���ݰ�
    xTaskCreate((TaskFunction_t )polling_mac_rx, 		
				(const char*	)"mac_rx_task",		
				(uint16_t		)1024, 
				(void*			)NULL,				
				(UBaseType_t	)1,	
				(TaskHandle_t*	)NULL);

    
#ifdef CHECKSUM_BY_HARDWARE 	//ʹ��Ӳ��֡У��
	for(i=0;i<ETH_TXBUFNB;i++)	//ʹ��TCP,UDP��ICMP�ķ���֡У��,TCP,UDP��ICMP�Ľ���֡У����DMA��������
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
#endif
	ETH_Start(); //����MAC��DMA
	printf("\r\n start eth");
	return ERR_OK;
}



//���ڷ������ݰ�����ײ㺯��(lwipͨ��netif->linkoutputָ��ú���)
//netif:�����ṹ��ָ��
//p:pbuf���ݽṹ��ָ��
//����ֵ:ERR_OK,��������
//       ERR_MEM,����ʧ��
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	u8 res;
	struct pbuf *q;
	int l = 0;
	u8 *buffer=(u8 *)ETH_GetCurrentTxBuffer(); 
	for(q=p;q!=NULL;q=q->next) 
	{
		memcpy((u8_t*)&buffer[l], q->payload, q->len);
		l=l+q->len;
	} 
	res=ETH_Tx_Packet(l); 
	if(res==ETH_ERROR)return ERR_MEM;//���ش���״̬
	return ERR_OK;
}



//���ڽ������ݰ�����ײ㺯��
//neitif:�����ṹ��ָ��
//����ֵ:pbuf���ݽṹ��ָ��
static struct pbuf * low_level_input(struct netif *netif)
{  
	struct pbuf *p, *q;
	u16_t len;
	int l =0;
	FrameTypeDef frame;
	u8 *buffer;
	p = NULL;
	frame=ETH_Rx_Packet();
	len=frame.length;//�õ�����С
	buffer=(u8 *)frame.buffer;//�õ������ݵ�ַ 
	p=pbuf_alloc(PBUF_RAW,len,PBUF_POOL);//pbufs�ڴ�ط���pbuf
	if(p!=NULL)
	{
		for(q=p;q!=NULL;q=q->next)
		{
			memcpy((u8_t*)q->payload,(u8_t*)&buffer[l], q->len);
			l=l+q->len;
		}    
	}
	frame.descriptor->Status=ETH_DMARxDesc_OWN;//����Rx������OWNλ,buffer�ع�ETH DMA 
	if((ETH->DMASR&ETH_DMASR_RBUS)!=(u32)RESET)//��Rx Buffer������λ(RBUS)�����õ�ʱ��,������.�ָ�����
	{ 
		ETH->DMASR=ETH_DMASR_RBUS;//����ETH DMA RBUSλ 
		ETH->DMARPDR=0;//�ָ�DMA����
	}
	return p;
}



//������������(lwipֱ�ӵ���)
//netif:�����ṹ��ָ��
//����ֵ:ERR_OK,��������
//       ERR_MEM,����ʧ��
err_t ethernetif_input(struct netif *netif)
{
	err_t err;
	struct pbuf *p;
	p=low_level_input(netif);
	if(p==NULL) return ERR_MEM;
	err=netif->input(p, netif);
	if(err!=ERR_OK)
	{
		LWIP_DEBUGF(NETIF_DEBUG,("ethernetif_input: IP input error\n"));
		pbuf_free(p);
		p = NULL;
	} 
	return err;
}



//ʹ��low_level_init()��������ʼ������
//netif:�����ṹ��ָ��
//����ֵ:ERR_OK,����
//       ����,ʧ��
err_t ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif!=NULL",(netif!=NULL));
#if LWIP_NETIF_HOSTNAME			//LWIP_NETIF_HOSTNAME 
	netif->hostname="lwip";  	//��ʼ������
#endif 
	netif->name[0]=IFNAME0; 	//��ʼ������netif��name�ֶ�
	netif->name[1]=IFNAME1; 	//���ļ��ⶨ�����ﲻ�ù��ľ���ֵ
	netif->output=etharp_output;//IP�㷢�����ݰ�����
	netif->linkoutput=low_level_output;//ARPģ�鷢�����ݰ�����
	low_level_init(netif); 		//�ײ�Ӳ����ʼ������
	return ERR_OK;
}














