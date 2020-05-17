/*******************************************************************************
COPYRIGHT:
    None
MODULE NAME:
    None
VERSION:
    1.00
DESCRIPTION:
    None
NOTES:
    None
HISTORY:
    Ver1.00:    2007.03.02    Panda Xiong(yaxi1984@gmail.com)    create;
*******************************************************************************/

#ifndef __UTL_VT_H__
#define __UTL_VT_H__

#include "usart.h"


#define ROM_VOID_T			void const*
#define ROM_READ_BYTE 		pgm_read_byte
#define pgm_read_byte(A)	(*(unsigned char  *)(A))
/* check pointer is NULL or not */
#define POINTER_CHECK(p)    ((p == NULL) ? 1 : 0)

/* Define key ascii value */
#define KEY_ESC	    (27)
#define KEY_ENTER   (13)
#define KEY_SPACE   (32)
#define KEY_BS      (8)
#define KEY_TAB     (9)
#define KEY_LF      (10)

#define KEY_DEL	        (0x7F)

#define KEY_CTRL_D      (0x04)
#define KEY_CTRL_L      (0x0C)
#define KEY_CTRL_C      (0x03)
#define KEY_CTRL_T      (0x14)
#define KEY_CTRL_R      (0x12)
#define KEY_CTRL_S      (0x13)
#define KEY_CTRL_U      (0x15)
#define KEY_CTRL_Z      (0x1A)

#define OTHER_KEY_BASE (200)

/* the keys below are not in the ascii table, so we should map them */
#define KEY_LEFT	(OTHER_KEY_BASE+0)
#define KEY_RIGHT	(OTHER_KEY_BASE+1)
#define KEY_UP		(OTHER_KEY_BASE+2)
#define KEY_DOWN	(OTHER_KEY_BASE+3)
#define KEY_F1		(OTHER_KEY_BASE+4)
#define KEY_F2		(OTHER_KEY_BASE+5)
#define KEY_F3		(OTHER_KEY_BASE+6)
#define KEY_F4		(OTHER_KEY_BASE+7)
#define KEY_HOME	(OTHER_KEY_BASE+8)
#define KEY_END		(OTHER_KEY_BASE+9)
#define KEY_INSERT	(OTHER_KEY_BASE+10)

#define KEY_BRACKET  '['
#define KEY_NULL     '\0'


//CLI命令行的获取和发送串口数据接口
#define UTL_VT_GetByte()            UartGetByte(UART_INDX_3)        //获取串口数据
#define UTL_VT_PutByte(c)           UartSendByte(UART_INDX_3,c)     //发送单个字符
#define UTL_VT_PutString            uart3_send_str                  //发送多个字符，define不能传递指针只能直接更换函数名
     




extern I8_T UTL_VT_ReadKey(void);
extern void UTL_VT_ClearRight(void);
extern void UTL_VT_MoveLeft( const UI8_T columns);
extern void UTL_VT_MoveRight( const UI8_T columns);
extern void UTL_VT_ClearScreen(void);
extern void UTL_VT_InitScreen(void);
extern void UTL_VT_PutAscii(const UI8_T *p_str, UI8_T size);
extern unsigned char CRC8_Table(unsigned char *p, char counter);
extern unsigned int CRC16_Table(unsigned char *pcrc, int count);






#endif /* __UTL_VT_H__ */

