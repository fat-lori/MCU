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

#include "basetype.h"
#include "utl_string.h"


UI8_T IP[6]={0,0,0,0,0,0};
#if 1
void *MEMSET(void *m, const I8_T c, int n);

UI32_T HEXTOUI32(const UI8_T *str)
{
	UI32_T n = 0;

	while (1)
	{
            if((*str >= '0') && (*str <= '9')){
		n = (n<<4 )| (*str - '0');
            }
            else if((*str >= 'a') && (*str <= 'f')){
		n = (n<<4 )| (*str - 'W');
            }
            else if((*str >= 'A') && (*str <= 'F')){
                n = (n<<4 )| (*str - '7');
            }
            else
              break;
	    str++;
	}

	return n;
}

UI64_T HEXTOUI64(const UI8_T *str)
{
	UI64_T n = 0;

	while (1)
	{
            if((*str >= '0') && (*str <= '9')){
		n = (n<<4 )| (*str - '0');
            }
            else if((*str >= 'a') && (*str <= 'f')){
		n = (n<<4 )| (*str - 'W');
            }
            else if((*str >= 'A') && (*str <= 'F')){
                n = (n<<4 )| (*str - '7');
            }
            else
              break;
	    str++;
	}

	return n;
}


void HEXTOUI8(const UI8_T *str,UI8_T *data)
{
	UI8_T i = 0;

	while (1)
	{
            if((*str >= '0') && (*str <= '9')){
		data[i] =  (*str - '0');
            }
            else if((*str >= 'a') && (*str <= 'f')){
		data[i] =  (*str - 'W');
            }
            else if((*str >= 'A') && (*str <= 'F')){
                data[i]  =  (*str - '7');
            }
            else
              break;
	    str++;
            
            if((*str >= '0') && (*str <= '9')){
		data[i] = (data[i] <<4 )| (*str - '0');
            }
            else if((*str >= 'a') && (*str <= 'f')){
		data[i] = (data[i] <<4 )| (*str - 'W');
            }
            else if((*str >= 'A') && (*str <= 'F')){
                data[i]  = (data[i]<<4 )| (*str - '7');
            }
            else
              break;
	    str++;
            i++;
	}

	return ;
}

I8_T ATOI8(const UI8_T *str)
{
	I8_T n = 0;

	while ((*str >= '0') && (*str <= '9'))
	{
		n = (n * 10) + *str - '0';
		str++;
	}

	return n;
}

I16_T ATOI16(const UI8_T *str)
{
	I16_T n = 0;

	while ((*str >= '0') && (*str <= '9'))
	{
		n = (n * 10) + *str - '0';
		str++;
	}

	return n;
}

UI8_T SEARCHIP(const UI8_T *str)
{
  UI8_T *temp=(UI8_T *)str;
  UI8_T count=0;
      while ((*temp != '\0') )
	  {    
	  	  temp++;
		  if((*(temp)=='.')||(*(temp)==':'))
		  count++;
	  }
	return  (count);
}

UI8_T *STRTOIP(const UI8_T *string)
{
    
     UI8_T *str=(UI8_T *)string;
	 MEMSET(IP,0,6);
	 while ((*str >= '0') && (*str <= '9'))
	 {
		 IP[0] = (IP[0] * 10) + *str - '0';
		 str++;
	 }
     str++;
	 while ((*str >= '0') && (*str <= '9'))
		 {
			 IP[1] = (IP[1] * 10) + *str - '0';
			 str++;
		 }
		 str++;
	 while ((*str >= '0') && (*str <= '9'))
	 {
		 IP[2] = (IP[2] * 10) + *str - '0';
		 str++;
	 }
     str++;
	  while ((*str >= '0') && (*str <= '9'))
	 {
		 IP[3] = (IP[3] * 10) + *str - '0';
		 str++;
	 }
     return (IP);

}

UI8_T *STRTOMAC(const UI8_T *str)
{
	MEMSET(IP,0,6);
	 while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[0] = (IP[0] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[0] = (IP[0] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[0] = (IP[0] * 16) + *str - 87;
			 str++;
	     }
	 }
     str++;
	  while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[1] = (IP[1] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[1] = (IP[1] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[1] = (IP[1] * 16) + *str - 87;
			 str++;
	     }
	 }
		 str++;
	 while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[2] = (IP[2] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[2] = (IP[2] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[2] = (IP[2] * 16) + *str - 87;
			 str++;
	     }
	 }
     str++;
	  while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[3] = (IP[3] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[3] = (IP[3] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[4] = (IP[3] * 16) + *str - 87;
			 str++;
	     }
	 }
	  str++;
	  while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[4] = (IP[4] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[4] = (IP[4] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[4] = (IP[4] * 16) + *str - 87;
			 str++;
	     }
	 }
     str++;
	  while (((*str >= '0') && (*str <= '9'))||((*str >= 'A') && (*str <= 'F'))||((*str >= 'a') && (*str <= 'f')))
	 {    
	     if((*str >= '0') && (*str <= '9'))
	     {
		 	IP[5] = (IP[5] * 16) + *str - '0';
			 str++;
	     }
		else if((*str >= 'A') && (*str <= 'F'))
	     {
		 	IP[5] = (IP[5] * 16) + *str - 55;
			 str++;
	     }
		else if((*str >= 'a') && (*str <= 'f'))
	     {
		 	IP[5] = (IP[5] * 16) + *str - 87;
			 str++;
	     }
	 }
     return (IP);

}

double STRTOD(const UI8_T * s, UI8_T ** endptr)

{

   const UI8_T *  p     = s;
   double  value = 0;

    int                   sign  = 0;
    double                factor;
    unsigned int          expo;

  

    while ( (*p)==' ' )//跳过前面的空格
      p++;

    if(*p == '-' || *p == '+')
      sign = *p++;//把符号赋给字符sign，指针后移。

   //处理数字字符
    while ( (unsigned int)(*p - '0') < 10u )//转换整数部分
      value = value*10 + (*p++ - '0');

   //如果是正常的表示方式（如：1234.5678）
   if ( *p == '.' )
   {
        factor = 1.;
        p++;
        while ( (unsigned int)(*p - '0') < 10u )
      {
         factor *= 0.1;
            value  += (*p++ - '0') * factor;
        }
    }

   //如果是IEEE754标准的格式（如：1.23456E+3）
    if ( (*p | 32) == 'e' )
   {
      expo   = 0;
        factor = 10.L;

        switch (*++p)
      {
        case '-':
           factor = 0.1;
        case '+':
           p++;
           break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
           break;
        default :
           value = 0.L;
           p     = s;
           goto done;
        }

        while ( (unsigned int)(*p - '0') < 10u )
            expo = 10 * expo + (*p++ - '0');

        while ( 1 )
      {
        if ( expo & 1 )
           value *= factor;

            if ( (expo >>= 1) == 0 )
                break;

            factor *= factor;
        }
    }

done:
    if ( endptr != 0 )
        *endptr = (UI8_T *)p;

    return (sign == '-' ? -value : value);
}


UI8_T STRTOHEX(const UI8_T *str)
{
	UI8_T n = 0;
	if (str != NULL) 
	{
		while (*str != 0) 
		{
			char ch = *str++;
			if (ch != ' ') 
			{
				if (ch == '0' && (*str == 'x' || *str == 'X'))
				{
					str++;
					while (*str != 0) 
					{
						unsigned char uc = 0;
						if (*str >= '0' && *str <= '9') 
						{
							uc = (unsigned char)(*str - '0');
						} 
						else if (*str >= 'a' && *str <= 'f') 
						{
							uc = (unsigned char)(*str - 'a' + 10);
						} 
						else if (*str >= 'A' && *str <= 'F') 
						{
							uc = (unsigned char)(*str - 'A' + 10);
						} 
						else 
						{
							break;
						}
						n <<= 4;
						n |= uc;
						str++;
					}
				}
				break;
			}
		}
	}
	return n;
}






UI32_T STRTOHEX_UI32_T(const UI8_T *str)
{
	UI32_T n = 0;
	if (str != NULL) 
	{
		while (*str != 0) 
		{
			char ch = *str++;
			if (ch != ' ') 
			{
				if (ch == '0' && (*str == 'x' || *str == 'X'))
				{
					str++;
					while (*str != 0) 
					{
						UI32_T uc = 0;
						if (*str >= '0' && *str <= '9') 
						{
							uc = (unsigned char)(*str - '0');
						} 
						else if (*str >= 'a' && *str <= 'f') 
						{
							uc = (unsigned char)(*str - 'a' + 10);
						} 
						else if (*str >= 'A' && *str <= 'F') 
						{
							uc = (unsigned char)(*str - 'A' + 10);
						} 
						else 
						{
							break;
						}
						n <<= 4;
						n |= uc;
						str++;
					}
				}
				break;
			}
		}
	}
	return n;
}










float ATOF(UI8_T *str)

{

   return STRTOD(str,0);

}

void *MEMSET(void *m, const I8_T c, int n)
{
    UI8_T   *p  = (UI8_T *)m;
	while(n>0)
	{
		*p++=(unsigned char)c;
		--n;
	}
    return m;
}
I8_T MEMCMP(const void *s1v, const void *s2v, UI8_T size)
{
    UI8_T *s1 = (UI8_T *)s1v;
    UI8_T *s2 = (UI8_T *)s2v;
    I8_T   a, b;

    while (size-- != 0)
    {
        if ((a = *s1++) != (b = *s2++))
        {
            return (a - b);
        }
    }

    return 0;
}

void *MEMCPY(void *dst, const void *src, int len)
{
    UI8_T       *to   = (UI8_T *)dst;
    UI8_T       *from = (UI8_T *)src;

    while (len)
    {
        *to = *from;
		 from++;
		 to++;
		 --len;
    }

    return dst;
}


UI8_T STRLEN(const UI8_T *string)
{
    const UI8_T *ret = string;

	while (*string++ != '\0')
	{}

	return (UI8_T)((string - 1) - ret);
}

UI8_T STRLEN_(const UI8_T *string)
{
    const UI8_T *ret = string;

	while ((*string != '\0')&&(*string != '<')&&(*string != '['))
	{string++;}

	return (UI8_T)((string) - ret);
}


UI8_T *STRCPY(UI8_T *to, const UI8_T *from)
{
    UI8_T *ret = to;

	while ((*to++ = *from++) != '\0')
	{}

	return ret;
}


UI8_T  *STRCPY_RTOE(UI8_T *to,const  UI8_T   *from)
{

	while ((*to++ = *from++) != '\0')
	{}

	return 0;
}


UI8_T STRMCPY(UI8_T *to, const UI8_T *from)
{
    UI8_T count=0;

	while (1)
	{
          if(( *from != '\0')&&( *from != '[')&&( *from != '<'))
          {
            *to++ = *from++;
            count++;
          }
          else
            return count;
        }

	//return ret;
}

UI8_T *STRNCPY(UI8_T *to, const UI8_T *from, UI8_T count)
{
    UI8_T *ret = to;

	while (count > 0)
	{
		count--;
		if ((*to++ = *from++) == '\0')
		{
			break;
		}
	}

	while (count > 0)
	{
		count--;
		*to++ = '\0';
	}

	return ret;
}

I8_T STRCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
			return (a - b);
		}
	}
	return (a - b);
}

I8_T STRNCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
			if((a==' ')&&(b==' '))
	   			return 0;
			return (a - b);
		}
	}
	if((a==' ')||(b==' '))
	   return 0;
	return (a - b);
}


UI8_T STRLCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;
        UI8_T l=0;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
			return l;
		}
                l++;
	}

	return l;
}

I8_T STRMCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
			if((a=='[')||(a=='<'))
			{
				//UTL_VT_PutString("\n\r<>!");
				return 0;
			}
			else
				return (a - b);
		}
	}
       if((b==' ')||(a=='[')||(a=='<'))
	{
		//UTL_VT_PutString("\n\rnull!");
		return 0;
	}
	   
	return (a - b);
}

UI8_T SEARCHTIME(const UI8_T *str)
{
  UI8_T *temp=(UI8_T *)str;
  UI8_T count=0;
      while ((*temp != '\0') )
	  {    
	  	  temp++;
		  if((*(temp)=='-')||(*(temp)==':'))
		  count++;
	  }
	return  (count);
}




UI8_T STRTOTIME(const UI8_T *string,UI8_T *time_t)
{
     UI8_T *str=(UI8_T *)string;
	 int year=0;

	while ((*str >= '0') && (*str <= '9'))
    {
        year = (year * 10) + *str - '0';
        str++;
    }
    str++;
    while ((*str >= '0') && (*str <= '9'))
        {
            time_t[1] = (time_t[1] * 10) + *str - '0';
            str++;
        }
        str++;
    while ((*str >= '0') && (*str <= '9'))
    {
        time_t[2] = (time_t[2] * 10) + *str - '0';
        str++;
    }
    str++;
     while ((*str >= '0') && (*str <= '9'))
    {
        time_t[3] = (time_t[3] * 10) + *str - '0';
        str++;
    }    
    str++;
     while ((*str >= '0') && (*str <= '9'))
    {
        time_t[4] = (time_t[4] * 10) + *str - '0';
        str++;
    }
    str++;
    while ((*str >= '0') && (*str <= '9'))
    {
        time_t[5] = (time_t[5] * 10) + *str - '0';
        str++;
    }        
    time_t[0]=year%100;

     return 0;

}


#if 0
I8_T STRTCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
            if((a=='[')||(a=='<'))
			{

                if(b==' ')
                     return -1;
                else
                {
                                  
                     *s2--;
                     while((b>=0x2b)&&(b<=0x39))
                     	b=*s2++;
                                  
                     if(b=='\0')
                     	return 1;
                     else if(b==' ')
                        return 2;
                     else
                        return -1;
                                  
                                  
                                }
			}
			else
				return -1;
		}
	}
        
        if(b=='\0')
        {
          if(a=='\0')
            return 1;
          else
            return 0;

        }
        if(b==' ')
	{
	    return 2;
	}
		
        if ((a=='[')||(a=='<'))
        {
          return 0;
        }
	   
	return -1;
}
#endif

I8_T STRTCMP(const UI8_T *_s1, const UI8_T *_s2)
{
    UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	UI8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
			
            if((a=='[')||(a=='<'))
			{

                if(b==' ')
                     return -1;
                else
                {
                                  
                     *s2--;
                     while((b>=0x2b)&&(b<=0x39))
                     	b=*s2++;
                                  
                     if(b=='\0')
                     	return 1;
                     else if(b==' ')
                        return 2;
                     else
                        return -1;
                                  
                                  
                                }
			}
			else
				return -1;
		}
	}
        
        if(b=='\0')
        {
          if(a=='\0')
            return 1;
          else
            return 0;

        }
	
        if(b==' ')
	{
	//UTL_VT_PutByte(a);
	//	UTL_VT_PutString("\n\r I'am coming1");
	    return 2;
	}
		if (a=='<' || a=='[')
    {
     //  UTL_VT_PutString("\n\r I'am coming2");
          return 0;
    }
		
        
	   
	return -1;
}



I8_T STRSCMP(const UI8_T *_s1, const UI8_T *_s2)
{
        UI8_T *s1 = (UI8_T *)_s1;
	UI8_T *s2 = (UI8_T *)_s2;
	I8_T   a, b;

	while ((a = *s1++), (b = *s2++), a && b)
	{
		if (a != b)
		{
            if((a=='[')||(a=='<'))
			{

                                if(b==' ')
                                  return -1;
                                else
                                {
                                  
                                  *s2--;
                                  while((b!='\0')&&(b!=' '))
                                    b=*s2++;
                                  
                                  if(b=='\0')
                                    return 1;
                                  else if(b==' ')
                                    return 2;
                                  else
                                    return -1;
                                  
                                  
                                }
			}
			else
				return -1;
		}
	}
        
        if(b=='\0')
        {
          if(a=='\0')
            return 1;
          else
            return 0;

        }
        if(b==' ')
		{
	    return 2;
		}
        if ((a=='[')||(a=='<'))
        {
          return 0;
        }
	   
	return -1;
}


I8_T STRTOHEAD(const UI8_T *_s1, const UI8_T n)
{
    UI8_T *s1 = (UI8_T *)_s1;
	I8_T   i,j;
	UI8_T quotion_mark_flag = 0;

	i=0;
    j=n;
	while(1) 
	{
		while ((*s1== ' ') && ((quotion_mark_flag&0x1) == 0))
		{
			s1++;
			i++;
		}

		if(j>0)
		{
			while ((*s1!= ' ')&&(*s1!= 0) || ((quotion_mark_flag&0x1) == 1)&&(*s1!= 0))
			{
				if((*s1 == '"'))
					quotion_mark_flag++;
				s1++;
				i++;
			}
		}
		else
		    return i;	
		j--;
	}
       
}


UI8_T *STRSTR(const UI8_T *s1,const UI8_T *s2)

{
  UI8_T i;

   if (*s1 == 0)
    {
      if (*s2)
        return (UI8_T *) NULL;
      return (UI8_T *) s1;
    }
   
   while (*s1)
   {
      i = 0;
      while (1)
      {
        if (s2[i] == 0)
        {
           return (UI8_T *) s1;
        }

        if (s2[i] != s1[i])
        {
           break;
        }

        i++;
      }
      s1++;
   }

   return (UI8_T *) NULL;
}

#endif

void *P_MEMCPY(void *dst, ROM_VOID_T src, const UI8_T len)
{
    UI8_T  loop = 0;
    UI8_T *to = (UI8_T *)dst;

    while (loop != len)
    {
        *to = ROM_READ_BYTE((const unsigned char *)src + loop);
        to++;
        loop++;
    }

    return dst;
}


void *MEM1(UI8_T *dst, UI8_T *src, const UI8_T len)
{
    const UI8_T *end  = (UI8_T *)dst + len;
    UI8_T       *to   = (UI8_T *)dst;
    UI8_T       *from = (UI8_T *)src;

    for (; to < end; to++, from++)
    {
        *to = *from;
    }

    return dst;
}


I8_T STRTOQUOTE(const UI8_T *_s1, const UI8_T n)
{
    UI8_T *s1 = (UI8_T *)_s1;
	I8_T   i,j;

	i=0;
    j=n;
	while(1) 
	{
		while (*s1== '"') 
		{
			s1++;
			i++;
		}

		if(j>0)
		{
			while ((*s1!= '"')&&(*s1!= 0))
			{
				s1++;
				i++;
			}
		}
		else
		    return i;	
		j--;
	}
       
}

char *strnchr(char *p, char c, size_t n)
{
	if (!p)
		return (0);

	while (n-- > 0) {
		if (*p == c)
			return ((char *)p);
		if(*p == '\0')
			goto RET;
		p++;
	}
RET:
	return (0);
}

