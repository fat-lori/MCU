#include <string.h>
#include <stdbool.h>
#include "basetype.h"
#include "utl_string.h"
#include "cli.h"
#include "command.h"
#include "delay.h"






const CLI_CMD_T cli_cmd_debug_log[]         = CLI_DEBUG_LOG;
const CLI_CMD_T cli_cmd_debug[]             = CLI_DEBUG;


















const CLI_CMD_T   cli_cmd[]               = CLI_API_COMMANDS;				//所有的添加的命令行需要在此变量的上面，表示已声名
const CLI_CMD_T   cli_cmd_kernel[]        = CLI_API_COMMANDS_KERNEL;



#if CLI_HISTORY_ENABLE
UI8_T           cmd_history_buffer[CLI_MAX_HISTORY][CLI_CMDBUF_MAX_LEN + 1];
UI8_T           cmd_history_index=0;
#endif

UI8_T	cli_timeOut=0;
UI8_T   user_index=0; 
UI8_T   user_level=0; 
const CLI_ACCOUNT_T		cli_account_hide = {9, "ADMIN",    "admin",   DEBUG};
const CLI_ACCOUNT_T		cli_account_flash[CLI_CMD_MAX_ACCOUNT] = {1, "admin",    "admin",   ADMINISTRATOR};
unsigned char			Pass_word[17]="admin";
const UI8_T				ansiclr[CLEAR_SCREEN_LEN]={0x1b, 0x5b, 0x3b, 0x48, 0x1b, 0x5b, 0x32, 0x4a, 0};
const static UI8_T	print_unknown_command[]="\n\r Unknown command!";
const static UI8_T	cli_prompt[]= "\n\r-->";
const static UI8_T	cli_login[]= "\n\rLogin:";
const static UI8_T	cli_passwd[]= "\n\rPasswd:";
const static UI8_T  cli_noexist_user[]		= "\n\rUser does not exist";
const static UI8_T  cli_old_passwd[]		= "\n\rOld Passwd:";
const static UI8_T  cli_new_passwd[]		= "\n\rNew Passwd:";
const static UI8_T  cli_retype_passwd[]		= "\n\rRetype Passwd:";
const static UI8_T  cli_incorrect_passwd[]	= "\n\rThe password is incorrect";
const static UI8_T  cli_nomatch_passwd[]	= "\n\rPasswords do not match";
const static UI8_T  cli_cmd_help_prompt[]	= "\n\rAll commands:";
const  UI8_T  print_success[]               = "\n\r Done!";
const  UI8_T  print_fail[]                  = "\n\r Fail!";
const  UI8_T  print_parameter_error[]       = "\n\r Parameter error!";
const  UI8_T  print_portnum_error[]         = "\n\r Port number  error!";
const  UI8_T  print_port_disable[]          = "\n\r Port disable!";
const  UI8_T  print_module_not_inserted[]   = "\n\r Module  not inserted!";
const  UI8_T  print_unknow_error[]          = "\n\r Unknow error!";
const  UI8_T  print_not_support_function[]  = "\n\r Not spuuort this function!";
const  UI8_T  print_uncongnized_module[]    = "\n\r Uncongnized_module!";
const  UI8_T  print_linenum_error[]         = "\n\r Line number  error!";



void UTL_VT_ClearScreen(void)
{

    UI8_T  tmp[CLEAR_SCREEN_LEN];

    MEMSET(tmp, 0x0, sizeof(tmp));
    P_MEMCPY(tmp, (ROM_VOID_T)ansiclr, CLEAR_SCREEN_LEN);
    UTL_VT_PutString(tmp);

}



void CLI_Init(void)
{
    /* clear screen */
    UTL_VT_ClearScreen();
    
    while (1)
    {
        cli_MainProcess();
    }
}



UI8_T CLI_CMD_Help( const UI32_T n_param, const UI8_T *param[])
{

    CLI_CMD_INDEX_T total_index =0; //(sizeof(cli_cmd) / sizeof(cli_cmd[0]));
#if  CLI_CMD_MAX_LEN>CLI_HELP_MAX_LEN
    UI8_T           cmd[CLI_CMD_MAX_LEN + 1];
#else    
    UI8_T           cmd[CLI_HELP_MAX_LEN + 1];
#endif 
    UI8_T           i;
    CLI_CMD_INDEX_T index;
    const CLI_CMD_T     *temp_cmd=(const CLI_CMD_T   *)param[1];
    //temp=param[1];
    
    while(temp_cmd[total_index].index==total_index+1)
      total_index++;

    MEMSET(cmd, 0x0, CLI_CMD_MAX_LEN + 1);
    P_MEMCPY(cmd, (ROM_VOID_T)cli_cmd_help_prompt, CLI_CMD_MAX_LEN + 1);
    UTL_VT_PutString(cmd);

    for (index = 1; index <= total_index; index++)
    {
        if((user_level>=temp_cmd[index-1].level)&&(temp_cmd[index-1].level&0x01))
        {  
            MEMSET(cmd, 0x00, CLI_CMD_MAX_LEN + 1);
            P_MEMCPY(cmd, (ROM_VOID_T)temp_cmd[index-1].cmd, CLI_CMD_MAX_LEN + 1);
            UTL_VT_PutString("\n\r ");
            for(i=0;i<(CLI_CMD_MAX_LEN + 1);i++)
            {
              if(cmd[i]!=0)
                UTL_VT_PutByte(cmd[i]);
              else
                UTL_VT_PutByte(' ');
            }
            
            MEMSET(cmd, 0x0, CLI_HELP_MAX_LEN + 1);
            P_MEMCPY(cmd, (ROM_VOID_T)temp_cmd[index-1].help, CLI_HELP_MAX_LEN + 1);
            UTL_VT_PutString(cmd);
        }
    }



    return 0;
}



UI8_T CLI_CMD_N_Help( const UI32_T n_param,const CLI_CMD_T   *param)
{
#if  CLI_CMD_MAX_LEN>CLI_HELP_MAX_LEN
    UI8_T           cmd[CLI_CMD_MAX_LEN + 1];
#else    
    UI8_T           cmd[CLI_HELP_MAX_LEN + 1];
#endif    
    UI8_T           i;
    //CLI_CMD_INDEX_T index;
    //const CLI_CMD_T     *temp_cmd=(const CLI_CMD_T   *)param[1];    
   

        MEMSET(cmd, 0x00, CLI_CMD_MAX_LEN + 1);
        P_MEMCPY(cmd, (ROM_VOID_T)param[n_param-1].cmd, CLI_CMD_MAX_LEN + 1);
        UTL_VT_PutString("\n\r ");
        for(i=0;i<(CLI_CMD_MAX_LEN + 1);i++)
        {
          if(cmd[i]!=0)
            UTL_VT_PutByte(cmd[i]);
          else
            UTL_VT_PutByte(' ');
        }
        
        MEMSET(cmd, 0x0, CLI_HELP_MAX_LEN + 1);
        P_MEMCPY(cmd, (ROM_VOID_T)param[n_param-1].help, CLI_HELP_MAX_LEN + 1);
        UTL_VT_PutString(cmd);

    return 0;
}




UI8_T CLI_CMD_LOGOUT( const UI32_T n_param, const UI8_T *param[])
{
	user_index=0;
	user_level=0;
	UTL_VT_ClearScreen();

    return 0;
}



UI8_T CLI_CMD_ClearScreen( const UI32_T index, const UI8_T *data[])
{
    UTL_VT_ClearScreen();

    return 0;
}



UI8_T CLI_CMD_Prompt( const UI32_T index, const UI8_T *data[])
{
    UI8_T    *cmd_buff;
	cmd_buff=( UI8_T   *)data[0];

    
    cmd_buff=cmd_buff+STRTOHEAD(cmd_buff,1);

    if(cmd_buff[0] == '\0')
    {
      
      return 2;
    }
    return 0;
}






UI8_T CheckPwd( const UI8_T index, const UI8_T *start_addr)
{
    UI8_T           pwd[CLI_USER_MAX_LEN + 1];    

	//return 5;
    if((index>0)&&(index<9))
    {
        MEMSET(&pwd, 0x0,CLI_USER_MAX_LEN + 1);
        //STRCPY_ETOR(pwd,cli_account[index-1].password);
        MEMCPY(pwd,Pass_word,CLI_USER_MAX_LEN + 1);

        if (STRCMP(pwd, start_addr) == 0)
        {
            return 5;   //管理员权限
        }
    }
    else if(index==9)
    {
        MEMSET(&pwd, 0x0,CLI_USER_MAX_LEN + 1);
        P_MEMCPY(pwd,cli_account_hide.password,sizeof(pwd));

        if (STRCMP(pwd, start_addr) == 0)
        {
            return cli_account_hide.level;
        }
    }
    
    return 0;
}

UI8_T SearchUser( const UI8_T *start_addr)
{
    //const UI8_T total_index = CLI_CMD_MAX_ACCOUNT;
    const UI8_T total_index = CLI_CMD_MAX_ACCOUNT;
    UI8_T  index;
    UI8_T           user[CLI_USER_MAX_LEN + 1]; 


    if (POINTER_CHECK(start_addr))
    {
        return 0;
    }
     
     
    for (index = 1; index <= total_index; index++)
    {
      
        if (STRCMP("admin", start_addr) == 0)
        {
            return index;
        }
    }
    
        MEMSET(&user, 0x0,CLI_USER_MAX_LEN + 1);
        P_MEMCPY(user,cli_account_hide.user,sizeof(user));
        
        if (STRCMP(user, start_addr) == 0)
        {
            return 9;
        }
    /* not found command */
    return 0;
}




UI8_T cli_TabMatchCmd( const UI32_T n,  UI8_T *start_addr,const CLI_CMD_T   *cli_cmd_addr,UI8_T **p_cmd_buf)
{
    CLI_CMD_INDEX_T total_index=0;
    CLI_CMD_INDEX_T  index;
    UI8_T           cmd_buffer[CLI_CMD_MAX_LEN + 1],cmd_temp[CLI_CMD_MAX_LEN + 1];
    UI8_T  len,l;	
    UI8_T  match_num=0;
    I8_T  match[16][2];
    I8_T  temp;


    //MEMSET(&cmd, 0x0, sizeof(cmd));

    if (POINTER_CHECK(start_addr))
    {
        return 0;
    }
    
    while(cli_cmd_addr[total_index].index==total_index+1)
      total_index++;
   
    len=STRTOHEAD(start_addr,n);
    
		
    for (index = 1; index <= total_index; index++)
    {
        if((user_level>=cli_cmd_addr[index-1].level)&&(cli_cmd_addr[index-1].level&0x01))
        {
            MEMSET(&cmd_buffer, 0x0, sizeof(cmd_buffer));
            P_MEMCPY(&cmd_buffer, (ROM_VOID_T)&cli_cmd_addr[index-1].cmd, sizeof(cli_cmd_addr[0].cmd));
                    
            switch(cli_cmd_addr[index-1].type)
            {
            case NONE:
              if( (temp=STRTCMP(cmd_buffer, start_addr+len))>=0)
              {    
                match[match_num][0]=index;
                match[match_num][1]=temp;
                match_num++;  
              }    
              break;
            case INT:
              if( (temp=STRTCMP(cmd_buffer, start_addr+len))>=0)
              {    
                match[match_num][0]=index;
                match[match_num][1]=temp;
                match_num++;  
              }  
              break;
            case STRING:
              if( (temp=STRSCMP(cmd_buffer, start_addr+len))>=0)
              {    
                match[match_num][0]=index;
                match[match_num][1]=temp;
                match_num++;  
              }  
              break;
            }
                 
        }
    }
    

    if(match_num==1)
    {
      
      switch(match[0][1])
      {
      case 0:     //部分匹配，补齐命令
            MEMSET(&cmd_buffer, 0x0, sizeof(cmd_buffer));
            P_MEMCPY(&cmd_buffer, (ROM_VOID_T)&cli_cmd_addr[match[0][0]-1].cmd, sizeof(cli_cmd_addr[0].cmd));
            
            if((temp=*p_cmd_buf-start_addr-len)<STRLEN_(cmd_buffer))
            {
              len=STRMCPY(start_addr+len,cmd_buffer);
              UTL_VT_PutString(*p_cmd_buf);
              *p_cmd_buf=*p_cmd_buf+len-temp;
              **p_cmd_buf   = '\0';
            }
        break;
      case 1:    //完全匹配，补空格
        if(cli_cmd_addr[match[0][0]-1].next_cmd !=NULL)           //存在下一级命令，继续搜索命令  
        {
          if (*p_cmd_buf != (start_addr + CLI_CMD_MAX_LEN))
          {
              
              **p_cmd_buf  = ' ';
              (*p_cmd_buf)++;
              **p_cmd_buf   = '\0';
              UTL_VT_PutByte(' ');
          }
        }
        else
        { 
            if(STRTOHEAD(start_addr,n+1)==STRTOHEAD(start_addr,n+2))
            {
              UTL_VT_PutString("\n\r Command complete!");
              
              MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
              P_MEMCPY(cmd_buffer, (ROM_VOID_T)cli_prompt, sizeof(cli_prompt));
              UTL_VT_PutString(cmd_buffer);
              UTL_VT_PutString(start_addr);
            }
            
        }
        break;
      case 2:    //完全匹配，匹配下一级命令
         if(cli_cmd_addr[match[0][0]-1].next_cmd !=NULL)           //存在下一级命令，继续搜索命令  
         {
           return cli_TabMatchCmd(n+1,start_addr,cli_cmd_addr[match[0][0]-1].next_cmd,p_cmd_buf);
         }
         else
         {
           
            if(STRTOHEAD(start_addr,n+1)==STRTOHEAD(start_addr,n+2))
            {
              UTL_VT_PutString("\n\r Command complete!");
              
              MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
              P_MEMCPY(cmd_buffer, (ROM_VOID_T)cli_prompt, sizeof(cli_prompt));
              UTL_VT_PutString(cmd_buffer);
              UTL_VT_PutString(start_addr);
            }
            
         }
         break;
		case 3:
			UTL_VT_PutString("\n\r next");
			UTL_VT_PutString(cli_cmd_addr[match[0][0]].cmd);
			break;
			
      default:
        break;
      }
    }
    else if(match_num>1)       //打印匹配命令
    {
      
      for(temp=0;temp<match_num;temp++)
      {
        CLI_CMD_N_Help(match[temp][0],cli_cmd_addr);
      }
      
      l=CLI_CMD_MAX_LEN;
      
        MEMSET(&cmd_buffer, 0x0, sizeof(cmd_buffer));
        P_MEMCPY(&cmd_buffer, (ROM_VOID_T)&cli_cmd_addr[match[0][0]-1].cmd, sizeof(cli_cmd_addr[0].cmd));
        
        for(temp=1;temp<match_num;temp++)
        {
          MEMSET(&cmd_temp, 0x0, sizeof(cmd_temp));
          P_MEMCPY(&cmd_temp, (ROM_VOID_T)&cli_cmd_addr[match[temp][0]-1].cmd, sizeof(cli_cmd_addr[0].cmd));

          len=STRLCMP(cmd_buffer, cmd_temp);
          if(l>len)
            l=len;
        }
        if((STRTOHEAD(start_addr,n+1)-STRTOHEAD(start_addr,n))<l)
        {
          len=STRTOHEAD(start_addr,n);

        
          STRNCPY(start_addr+len,cmd_buffer,l);
          *p_cmd_buf=start_addr+len+l;
          **p_cmd_buf   = '\0';
        }  
      
      MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
      P_MEMCPY(cmd_buffer, (ROM_VOID_T)cli_prompt, sizeof(cli_prompt));
      UTL_VT_PutString(cmd_buffer);
      UTL_VT_PutString(start_addr);
    }  
    
    return 0;
    
    
}



I8_T UTL_VT_ReadLine(  UI8_T  buf_len, UI8_T  *cmd_buffer, const UI8_T  password)
{
    UI8_T           key_value;
    UI8_T           *p_cmd_buf;
	
    MEMSET(cmd_buffer, 0x0, buf_len);
    p_cmd_buf = cmd_buffer;
    
    if ((buf_len == 0) || (cmd_buffer == NULL))
    {
        return -1;
    }
   
    while ((key_value = UTL_VT_ReadKey()) != KEY_ENTER)
    {
		msleep(10);
        switch (key_value)
        {
            case KEY_BS:
                if (p_cmd_buf != cmd_buffer)
                {
                    *(--p_cmd_buf) = '\0';
                    UTL_VT_PutString(CLI_BS_ASCII);
                }
                break;
            default:
                if ((key_value >= 0x20) && (key_value <= 0x7F))
                {
                    /* not to the end of buffer */
                    if (p_cmd_buf != (cmd_buffer + buf_len))
                    {
                        *p_cmd_buf++ = key_value;
                        *p_cmd_buf   = '\0';
                        if(password)
                          UTL_VT_PutByte('*');
                        else
                          UTL_VT_PutAscii(&key_value, 1);
						 //   UTL_VT_PutAscii(&key_value, 1);
                    }
                }
                break;
            }		
	 		
	 		
    }    
    if (cmd_buffer[0] == '\0')
    {
        return -1;
    }
    
    return 0;
}



UI8_T cli_Search_ExecuteCmd( const UI32_T n, const UI8_T *start_addr,const CLI_CMD_T   *cli_cmd_addr)
{
    //CLI_CMD_INDEX_T total_index = (sizeof(cli_cmd_addr) / sizeof(cli_cmd_addr[0]));
    CLI_CMD_INDEX_T total_index=0;
    CLI_CMD_INDEX_T  index;
    UI8_T           cmd_buffer[CLI_CMD_MAX_LEN + 1];
    UI8_T  len;	
    
    CLI_CMD_EXEC_T  p_exec_func;
     const UI8_T  *commandParams[2];
	commandParams[0]=(UI8_T  *)start_addr;
	commandParams[1]=(UI8_T  *)cli_cmd_addr;

    //MEMSET(&cmd, 0x0, sizeof(cmd));

    if (POINTER_CHECK(start_addr))
    {
        return 0;
    }
    
    while(cli_cmd_addr[total_index].index==total_index+1)
      total_index++;
   
    len=STRTOHEAD(start_addr,n);
		
    for (index = 1; index <= total_index; index++)
    {
        if((user_level+1)>=cli_cmd_addr[index-1].level)
        {
          MEMSET(&cmd_buffer, 0x0, sizeof(cmd_buffer));
          P_MEMCPY(&cmd_buffer, (ROM_VOID_T)&cli_cmd_addr[index-1].cmd, sizeof(cli_cmd_addr[0].cmd));
          if(*(start_addr+len)=='?')
          	{
			  index = total_index+1;
			   break;

		  }
          if (STRMCMP(cmd_buffer, start_addr+len) == 0)
          {
			//UartSendStr("\n\r command found");
            break;
			
          }             
        }
    }
    
    if(index>total_index)
    {
        cli_cmd_addr=cli_cmd_kernel;
        total_index = (sizeof(cli_cmd_kernel) / sizeof(cli_cmd_kernel[0]));
        for (index = 1; index <= total_index; index++)
        {
            if((user_level+1)>=cli_cmd_addr[index-1].level)
            {
              MEMSET(&cmd_buffer, 0x0, sizeof(cmd_buffer));
              P_MEMCPY(&cmd_buffer, (ROM_VOID_T)&cli_cmd_addr[index-1].cmd, sizeof(cli_cmd_addr[0].cmd));
                      
              if(cli_cmd_addr[index-1].type==INT){
           
                if( STRTCMP(cmd_buffer, start_addr+len)>=0)
                {    
                  break;
                }  
              }
              else if(cli_cmd_addr[index-1].type==STRING){
           
                if( STRSCMP(cmd_buffer, start_addr+len)>=0)
                {    
                  break;
                }  
              }
              else{
                if (STRMCMP(cmd_buffer, start_addr+len) == 0)
                {
                    break;
                } 
              }  
            }
        }
    
    }
    
    if(index>total_index)
      index=0;
    
    if(index !=0)     //搜索到命令
    {
         if(*(start_addr+STRTOHEAD(start_addr,n+1)) !='\0')    //命令没有结束
	{
          if(cli_cmd_addr[index-1].next_cmd !=NULL)           //存在下一级命令，继续搜索命令  
          {
            //cli_cmd_addr=cli_cmd_addr[index-1].next_cmd;
            return cli_Search_ExecuteCmd(n+1,start_addr,cli_cmd_addr[index-1].next_cmd);
          }  
          else                                       //没有下一级命令，返回无此命令 
          {
            UTL_VT_PutString(print_unknown_command);
            return 0;
          }
        }
        else
        {   
          if(cli_cmd_addr[index-1].cmd_exec !=NULL)         //命令结束，函数存在，执行函数
          {
            p_exec_func = cli_cmd_addr[index-1].cmd_exec;             // 命令结束，执行函数
            return (*p_exec_func)(2,commandParams);
          }
          else                            //函数不存在，返回无此命令
          {
            UTL_VT_PutString(print_unknown_command);
            return 0;
          }    
            
         
        }
          //return index;
    }
    
    /* not found command */
    UTL_VT_PutString("\n\r Unknown command!");
    
    return 0;
}


UI8_T CLI_CMD_ChangePasswd( const UI32_T n_param, const UI8_T *param[])
{
  
    UI8_T    old_buffer[CLI_USER_MAX_LEN + 1];
    UI8_T    new_buffer[CLI_USER_MAX_LEN + 1];
    UI8_T    *cmd_buff=( UI8_T   *)param[0];
    UI8_T     index;

    
    cmd_buff=cmd_buff+STRTOHEAD(cmd_buff,2);

    if(cmd_buff[0] != '\0')
    {
        index=SearchUser(cmd_buff);
        if(index==0)
        {
          UTL_VT_PutString(cli_noexist_user);
          return 1;
        }
    }
    else
    {
      index=user_index;
    }
    
    
    UTL_VT_PutString(cli_old_passwd);
    UTL_VT_ReadLine(CLI_USER_MAX_LEN,old_buffer,1);
    if(CheckPwd(index,old_buffer))
    {
        UTL_VT_PutString(cli_new_passwd);
        UTL_VT_ReadLine(CLI_USER_MAX_LEN,old_buffer,1);
        UTL_VT_PutString(cli_retype_passwd);
        UTL_VT_ReadLine(CLI_USER_MAX_LEN,new_buffer,1);
        if (STRCMP(old_buffer, new_buffer) == 0)
        { 
          MEMSET(Pass_word, 0x0, sizeof(Pass_word));
          MEMCPY(Pass_word,old_buffer,sizeof(old_buffer));

		  return 1;
        }
        else
        {
          UTL_VT_PutString(cli_nomatch_passwd);
        }
    }
    else
    {
        UTL_VT_PutString(cli_incorrect_passwd);
    }

    return 0;
}






UI8_T CLI_CMD_AccountFactory( const UI32_T index, const UI8_T *data[])
{
 	UI8_T    old_buffer[]="admin";

	MEMSET(Pass_word, 0x0, sizeof(Pass_word));
	MEMCPY(Pass_word,old_buffer,sizeof(old_buffer));

    return 0;
}



void cli_MainProcess(void)
{
    UI8_T           key_value;
    UI8_T           cmd_buffer[CLI_CMDBUF_MAX_LEN + 1];
    CLI_CMD_INDEX_T cmd_index;
    UI8_T          *p_cmd_buf;
    const CLI_CMD_T   *cli_cmd_addr=cli_cmd;
    bool            insertEnable =1;
#if CLI_HISTORY_ENABLE
    UI8_T           cmd_history_count;
    UI8_T           temp;  
#endif
    
   

    /* display prompt message */

    MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
    P_MEMCPY(cmd_buffer, (ROM_VOID_T)cli_prompt, sizeof(cli_prompt));
    UTL_VT_PutString(cmd_buffer);

 
    MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
    p_cmd_buf = cmd_buffer;

#if CLI_HISTORY_ENABLE
    cmd_history_count=0;
#endif    
    while ((key_value = UTL_VT_ReadKey()) != KEY_ENTER)
    {  
        switch (key_value)
        {
            case KEY_CTRL_L: /* clear screen */
                UTL_VT_ClearScreen();
                return;
            case KEY_INSERT:  /* set insert/overwrite mode */
				insertEnable = (insertEnable)? 0 : 1;
				break;    
            case KEY_BS:
                if (p_cmd_buf == cmd_buffer)
                {
                  break;
                }
                if (p_cmd_buf == (cmd_buffer + strlen((char *)cmd_buffer)))
                {
                    *(--p_cmd_buf) = '\0';
                    UTL_VT_PutString(CLI_BS_ASCII);
                }
                else
                {
                  UI8_T *loop;

	          p_cmd_buf--;
                  UTL_VT_PutString("\b");
                  UTL_VT_ClearRight();
		  UTL_VT_PutString(p_cmd_buf+1);
		  UTL_VT_MoveLeft(cmd_buffer + strlen((char *)cmd_buffer) - p_cmd_buf-1);

		  for (loop = p_cmd_buf;loop <= (cmd_buffer + strlen((char *)cmd_buffer));loop++)
		  {
			*loop = *(loop+1);
		  }
                }
                break;
            case KEY_LEFT:
		if (p_cmd_buf > cmd_buffer)
		{
			p_cmd_buf--;
			UTL_VT_MoveLeft(1);
		}
		break;

            case KEY_RIGHT:
		if (p_cmd_buf < (cmd_buffer + strlen((char *)cmd_buffer)))
		{
			p_cmd_buf++;
			UTL_VT_MoveRight(1);
		}
		break;        

	     case KEY_TAB:
                  cli_TabMatchCmd(0,cmd_buffer,cli_cmd_addr,&p_cmd_buf);
                  break;	
                  
#if CLI_HISTORY_ENABLE                  
             case KEY_UP:
                if(cmd_history_count<CLI_MAX_HISTORY)
                    cmd_history_count++;
                else
                  break;
                if(cmd_history_index<cmd_history_count)
                  temp=CLI_MAX_HISTORY+cmd_history_index-cmd_history_count;
                else
                  temp=cmd_history_index-cmd_history_count;
                if(cmd_history_buffer[temp][0] != '\0')
                {
                  while (p_cmd_buf != cmd_buffer)
                  {
                      *(--p_cmd_buf) = '\0';
                      UTL_VT_PutString(CLI_BS_ASCII);
                  }
                  
                  MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
                  STRCPY(cmd_buffer,cmd_history_buffer[temp]);
                  p_cmd_buf=cmd_buffer+STRTOHEAD(cmd_buffer,CLI_MAX_HISTORY_SPACE);     //上下键获取历史命令，p_cmd_buf是获取最大CLI_MAX_HISTORY_SPACE个空格后地址
                  UTL_VT_PutString(cmd_buffer);       
                }
                break;	
            case KEY_DOWN:
                if(cmd_history_count>1)
                    cmd_history_count--;
                else
                {
                  cmd_history_count=0;
                  while (p_cmd_buf != cmd_buffer)
                  {
                      *(--p_cmd_buf) = '\0';
                      UTL_VT_PutString(CLI_BS_ASCII);
                  }
                  break;
                }
                  
                if(cmd_history_index<cmd_history_count)
                  temp=CLI_MAX_HISTORY+cmd_history_index-cmd_history_count;
                else
                  temp=cmd_history_index-cmd_history_count;
                if(cmd_history_buffer[temp][0] != '\0')
                {
                  while (p_cmd_buf != cmd_buffer)
                  {
                      *(--p_cmd_buf) = '\0';
                      UTL_VT_PutString(CLI_BS_ASCII);
                  }
                  
                  MEMSET(cmd_buffer, 0x0, sizeof(cmd_buffer));
                  STRCPY(cmd_buffer,cmd_history_buffer[temp]);
                  p_cmd_buf=cmd_buffer+STRTOHEAD(cmd_buffer,CLI_MAX_HISTORY_SPACE);
                  UTL_VT_PutString(cmd_buffer);       
                }
                break;
#endif                

            default:
                if ((key_value < 0x20) ||(key_value > 0x7F))
                {
                  break;
                }
                    /* not to the end of buffer */
                if (p_cmd_buf >= (cmd_buffer + CLI_CMDBUF_MAX_LEN))
                {
                  break;
                }
                //L_VT_PutINT(strlen((char *)cmd_buffer));
                if (p_cmd_buf == (cmd_buffer + strlen((char *)cmd_buffer)))
                {
                      *p_cmd_buf++ = key_value;
                      *p_cmd_buf   = '\0';
                      UTL_VT_PutAscii(&key_value, 1);
                }
                else
                {
                      if (insertEnable) /* insert mode */
		      {
			    UI8_T *loop;
                            UTL_VT_PutAscii(&key_value, 1);
                            UTL_VT_PutString(p_cmd_buf);
			    UTL_VT_MoveLeft(cmd_buffer + strlen((char *)cmd_buffer) - p_cmd_buf);

			    for (loop = (cmd_buffer + strlen((char *)cmd_buffer));loop > p_cmd_buf;loop--)
			    {
				*loop = *(loop-1);
			    }
			    *p_cmd_buf++ = key_value;
			}
                        else
                        {  
                            *p_cmd_buf++ = key_value;
                            UTL_VT_PutAscii(&key_value, 1);
                        }
                }
                break;
        }

        /******************************************************/
       
//		send_watchdog_feed_cmd(CLI_WDOG_FEED_ID);
		msleep(10);
		if(cli_timeOut <= 0)
		{
		  user_index=0; 
		  user_level=0;
		}	

        /******************************************************/
    }
    
    
    
    
    /* No command input */
    if (cmd_buffer[0] == '\0')
    {
        return;
    }
    
    
    if ( (cmd_index=cli_Search_ExecuteCmd(0,cmd_buffer,cli_cmd_addr)) != 0)
    {
        /* found command, and execute the input command */
        switch(cmd_index)
        {
			case CLI_SUCCESS:
			  UTL_VT_PutString(print_success);
			  break;
			case CLI_FAIL:
			  UTL_VT_PutString(print_fail);
			  break;
			case CLI_PARAMETER_ERROR:
			  UTL_VT_PutString(print_parameter_error);  
			  break;
			case CLI_PORTNUM_ERROR:
			  UTL_VT_PutString(print_portnum_error);  
			  break;
			case CLI_PORT_DISABLE:
			  UTL_VT_PutString(print_port_disable);  
			  break;
			case CLI_MODULE_NOT_INSERT:
			  UTL_VT_PutString(print_module_not_inserted);  
			  break;
			case CLI_NOT_SUPPORT_FUNCTION:	
			  UTL_VT_PutString(print_not_support_function);  
			  break;
			case CLI_UNRECONGNIZED_MODULE:
			  UTL_VT_PutString(print_uncongnized_module);
			  break;
			case CLI_LINENUM_ERROR:
				UTL_VT_PutString(print_linenum_error);
				break;
			default:
			  UTL_VT_PutString(print_unknow_error);
			  break;
        }
    }
    
    /* save history command*/

#if CLI_HISTORY_ENABLE    
    STRCPY(cmd_history_buffer[cmd_history_index],cmd_buffer);
    cmd_history_index++;
    if(cmd_history_index==CLI_MAX_HISTORY)
      cmd_history_index=0;
#endif    

}


void cli_UserLogin(void)
{
    UI8_T           cmd_buffer[CLI_USER_MAX_LEN + 1];


    UTL_VT_PutString(CLI_CRLF);
    UTL_VT_PutString(CLI_CRLF);
    UTL_VT_PutString(cli_login);
    UTL_VT_ReadLine(CLI_USER_MAX_LEN,cmd_buffer,0);

    if(cmd_buffer[0]!='\0')
      user_index=SearchUser(cmd_buffer);
    else
      user_index=0;
    UTL_VT_PutString(cli_passwd);
    UTL_VT_ReadLine(CLI_USER_MAX_LEN,cmd_buffer,1);
      if(user_index)
      {
        user_level=CheckPwd(user_index,cmd_buffer);
      }
      else
      {
        user_level=0;
      }
        
      if(user_level==0)
      {
        user_index=0;
      }
      else
      {
        UTL_VT_ClearScreen();
        UTL_VT_InitScreen();
        UTL_VT_PutString(CLI_CRLF);
        UTL_VT_PutString(CLI_CRLF);
      }
   
    /* found user, and return user index */
      
     return;
}

void cli_timeout_count(void)
{
	if(cli_timeOut>0)
	{
		 cli_timeOut--;
	}
}

