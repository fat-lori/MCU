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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ethernetif.c 代码	   
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
        return;       //内存申请失败
    }

    struct netif *Netif_Init_Flag;		//调用netif_add()函数时的返回值,用于判断网络初始化是否成功
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

#if LWIP_DHCP	   			//若使用了DHCP
    int err;
    /*  Creates a new DHCP client for this interface on the first call.
    Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
    the predefined regular intervals after starting the client.
    You can peek in the netif->dhcp struct for the actual DHCP status.*/

    printf("\r\n 本例程将使用DHCP动态分配IP地址,如果不需要则在lwipopts.h中将LWIP_DHCP定义为0");

    err = dhcp_start(&gnetif);      //开启dhcp
    if(err == ERR_OK)
    printf("\r\n lwip dhcp init success...");
    else
    printf("\r\n lwip dhcp init fail...");
    while(ip_addr_cmp(&(gnetif.ip_addr),&ipaddr))   //等待dhcp分配的ip有效
    {
    vTaskDelay(1);
    } 
#endif
    printf("\r\n 本地IP地址是:%d.%d.%d.%d",      ((gnetif.ip_addr.addr)&0x000000ff),       \
                                            (((gnetif.ip_addr.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.ip_addr.addr)&0x00ff0000)>>16), \
                                            ((gnetif.ip_addr.addr)&0xff000000)>>24);
    printf("\r\n 本地MASK地址是:%d.%d.%d.%d",      ((gnetif.netmask.addr)&0x000000ff),       \
                                            (((gnetif.netmask.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.netmask.addr)&0x00ff0000)>>16), \
                                            ((gnetif.netmask.addr)&0xff000000)>>24);
    printf("\r\n 本地GW地址是:%d.%d.%d.%d",      ((gnetif.gw.addr)&0x000000ff),       \
                                            (((gnetif.gw.addr)&0x0000ff00)>>8),  \
                                            (((gnetif.gw.addr)&0x00ff0000)>>16), \
                                            ((gnetif.gw.addr)&0xff000000)>>24);
}



SemaphoreHandle_t BinarySemaphoreMacRx = NULL;

 //用于以太网中断调用
void lwip_pkt_handle(void)
{
    BaseType_t pxHigherPriorityTaskWoken;
	xSemaphoreGiveFromISR(BinarySemaphoreMacRx, &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
}


//与上面的handle相关联，有中断就调用次函数，将接收数据传递至LWIP内核中
void polling_mac_rx(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(BinarySemaphoreMacRx, portMAX_DELAY);
        while(ETH_GetRxPktSize(DMARxDescToGet)!=0)  //检测是否收到数据包
        {
            ethernetif_input(&gnetif);
        }
        
	}
}


 
//由ethernetif_init()调用用于初始化硬件
//netif:网卡结构体指针 
//返回值:ERR_OK,正常
//       其他,失败
static err_t low_level_init(struct netif *netif)
{
#ifdef CHECKSUM_BY_HARDWARE
	int i; 
#endif 
	netif->hwaddr_len = ETHARP_HWADDR_LEN; //设置MAC地址长度,为6个字节
	//初始化MAC地址,设置什么地址由用户自己设置,但是不能与网络中其他设备MAC地址重复
	netif->hwaddr[0]=MAC0; 
	netif->hwaddr[1]=MAC1; 
	netif->hwaddr[2]=MAC2;
	netif->hwaddr[3]=MAC3;
	netif->hwaddr[4]=MAC4;
	netif->hwaddr[5]=MAC5;
	netif->mtu=1500; //最大允许传输单元,允许该网卡广播和ARP功能
	//并且该网卡允许有硬件链路连接
	netif->flags = NETIF_FLAG_BROADCAST|NETIF_FLAG_ETHARP|NETIF_FLAG_LINK_UP;
	
	ETH_MACAddressConfig(ETH_MAC_Address0, netif->hwaddr); //向STM32F4的MAC地址寄存器中写入MAC地址
	ETH_DMATxDescChainInit(DMATxDscrTab, Tx_Buff, ETH_TXBUFNB);
	ETH_DMARxDescChainInit(DMARxDscrTab, Rx_Buff, ETH_RXBUFNB);

    //创建计数信号量，来计数MAC中断次数
    BinarySemaphoreMacRx = xSemaphoreCreateBinary();
    if (BinarySemaphoreMacRx == NULL)
        printf("\r\n create MAC RX semaphore fail");

    //创建任务，根据中断不停获取MAC数据包
    xTaskCreate((TaskFunction_t )polling_mac_rx, 		
				(const char*	)"mac_rx_task",		
				(uint16_t		)1024, 
				(void*			)NULL,				
				(UBaseType_t	)1,	
				(TaskHandle_t*	)NULL);

    
#ifdef CHECKSUM_BY_HARDWARE 	//使用硬件帧校验
	for(i=0;i<ETH_TXBUFNB;i++)	//使能TCP,UDP和ICMP的发送帧校验,TCP,UDP和ICMP的接收帧校验在DMA中配置了
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
#endif
	ETH_Start(); //开启MAC和DMA
	printf("\r\n start eth");
	return ERR_OK;
}



//用于发送数据包的最底层函数(lwip通过netif->linkoutput指向该函数)
//netif:网卡结构体指针
//p:pbuf数据结构体指针
//返回值:ERR_OK,发送正常
//       ERR_MEM,发送失败
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
	if(res==ETH_ERROR)return ERR_MEM;//返回错误状态
	return ERR_OK;
}



//用于接收数据包的最底层函数
//neitif:网卡结构体指针
//返回值:pbuf数据结构体指针
static struct pbuf * low_level_input(struct netif *netif)
{  
	struct pbuf *p, *q;
	u16_t len;
	int l =0;
	FrameTypeDef frame;
	u8 *buffer;
	p = NULL;
	frame=ETH_Rx_Packet();
	len=frame.length;//得到包大小
	buffer=(u8 *)frame.buffer;//得到包数据地址 
	p=pbuf_alloc(PBUF_RAW,len,PBUF_POOL);//pbufs内存池分配pbuf
	if(p!=NULL)
	{
		for(q=p;q!=NULL;q=q->next)
		{
			memcpy((u8_t*)q->payload,(u8_t*)&buffer[l], q->len);
			l=l+q->len;
		}    
	}
	frame.descriptor->Status=ETH_DMARxDesc_OWN;//设置Rx描述符OWN位,buffer重归ETH DMA 
	if((ETH->DMASR&ETH_DMASR_RBUS)!=(u32)RESET)//当Rx Buffer不可用位(RBUS)被设置的时候,重置它.恢复传输
	{ 
		ETH->DMASR=ETH_DMASR_RBUS;//重置ETH DMA RBUS位 
		ETH->DMARPDR=0;//恢复DMA接收
	}
	return p;
}



//网卡接收数据(lwip直接调用)
//netif:网卡结构体指针
//返回值:ERR_OK,发送正常
//       ERR_MEM,发送失败
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



//使用low_level_init()函数来初始化网络
//netif:网卡结构体指针
//返回值:ERR_OK,正常
//       其他,失败
err_t ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif!=NULL",(netif!=NULL));
#if LWIP_NETIF_HOSTNAME			//LWIP_NETIF_HOSTNAME 
	netif->hostname="lwip";  	//初始化名称
#endif 
	netif->name[0]=IFNAME0; 	//初始化变量netif的name字段
	netif->name[1]=IFNAME1; 	//在文件外定义这里不用关心具体值
	netif->output=etharp_output;//IP层发送数据包函数
	netif->linkoutput=low_level_output;//ARP模块发送数据包函数
	low_level_init(netif); 		//底层硬件初始化函数
	return ERR_OK;
}














