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

#ifndef __UTL_STRING_H__
#define __UTL_STRING_H__
#include "utl_vt.h"


extern UI8_T *STRTOIP(const UI8_T *string);   //字符串转换为IP
extern UI8_T SEARCHIP(const UI8_T *str);      //查询输入字符串中的"."个数
extern UI8_T *STRTOMAC(const UI8_T *str);  //字符串转换为MAC
extern UI8_T STRTOHEX(const UI8_T *str);

extern UI64_T HEXTOUI64(const UI8_T *str);
extern UI32_T HEXTOUI32(const UI8_T *str);
extern void HEXTOUI8(const UI8_T *str,UI8_T *data);
extern I8_T ATOI8(const UI8_T *str);    //字符串转换为数字
extern I16_T ATOI16(const UI8_T *str);

extern double STRTOD(const UI8_T * s, UI8_T ** endptr);//字符串转换成浮点数

extern float ATOF(UI8_T *str);

extern void *MEMSET(void *m, const I8_T c, int n);


extern void *MEM1(UI8_T *dst, UI8_T *src, const UI8_T len);


extern I8_T MEMCMP(const void *s1v, const void *s2v, UI8_T size);


extern UI8_T STRLEN(const UI8_T *string);

extern UI8_T STRLEN_(const UI8_T *string);

extern UI8_T *STRCPY(UI8_T *to, const UI8_T *from);

extern void *MEMCPY(void *dst, const void *src, int len);


extern UI8_T STRMCPY(UI8_T *to, const UI8_T *from);
extern UI8_T STRTOTIME(const UI8_T *string,UI8_T *time_t);

extern UI8_T SEARCHTIME(const UI8_T *str);

extern UI8_T *STRNCPY(UI8_T *to, const UI8_T *from, UI8_T count);

extern I8_T STRCMP(const UI8_T *_s1, const UI8_T *_s2);
extern I8_T STRNCMP(const UI8_T *_s1, const UI8_T *_s2);
extern UI8_T STRLCMP(const UI8_T *_s1, const UI8_T *_s2);

extern I8_T STRMCMP(const UI8_T *_s1, const UI8_T *_s2);

extern I8_T STRTCMP(const UI8_T *_s1, const UI8_T *_s2);
extern I8_T STRSCMP(const UI8_T *_s1, const UI8_T *_s2);

extern I8_T STRTOHEAD(const UI8_T *_s1, const UI8_T n);

extern void *P_MEMCPY(void *dst, ROM_VOID_T src, const UI8_T len);

extern UI8_T *STRSTR(const UI8_T *s1,const UI8_T *s2);
extern UI8_T  *STRCPY_RTOE(UI8_T *to,const  UI8_T   *from);
extern UI32_T STRTOHEX_UI32_T(const UI8_T *str);

extern I8_T STRTOQUOTE(const UI8_T *_s1, const UI8_T n);
extern char *strnchr(char *p, char c, size_t n);



void *P_MEMCPY(void *dst, ROM_VOID_T src, const UI8_T len);



#endif /* __UTL_STRING_H__ */

