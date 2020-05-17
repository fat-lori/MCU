#ifndef __CLI_H__
#define __CLI_H__

#include "utl_vt.h"

extern  UI8_T user_index;
extern  UI8_T cli_timeOut;


/*******************************************************************************
 *  CLI external define
*******************************************************************************/




#define CLI_API_COMMANDS_KERNEL                                         \
{                                                                       \
    {1, "?",      HIDE,  NONE,  "--show help information",   CLI_CMD_Help,        NULL},       \
    {2, "help",   HIDE,  NONE,  "--show help information",   CLI_CMD_Help,        NULL},       \
}




#define CLI_API_COMMANDS                                                \
{                                                                       \
    {1, "debug",  GUEST,		NONE,   "--debug conmmands",    	    NULL,                cli_cmd_debug},    \
    {2, "logout", GUEST,		NONE,   "--logout commands line",    	CLI_CMD_LOGOUT,      NULL},              \
    {3, "cls",    GUEST,		NONE,   "--clear screen",            	CLI_CMD_ClearScreen, NULL},              \
    {4, "boot",   GUEST,		NONE,   "--clear screen",            	CLI_CMD_SystemRestart, NULL},              \
}

#define CLI_DEBUG                                                       \
{{1, "log_level",  GUEST,		NONE,   "--set log level",    	    NULL,                cli_cmd_debug_log},}

#define CLI_DEBUG_LOG                                                       \
{{1, "<level>",  GUEST,		NONE,   "--set log level",    	    CLI_CMD_DEBUG_LEVEL,                NULL},}





/*******************************************************************************
 *  CLI internal define
*******************************************************************************/
#define CLI_BS_ASCII    ((const UI8_T *)"\b \b")
#define CLI_BS          ((const UI8_T *)"\b")
#define CLI_CRLF        ((const UI8_T *)"\n\r")
#define CLEAR_SCREEN_LEN     (9)
#define INIT_SCREEN_LEN      (128)


#define CLI_HISTORY_ENABLE      (1)
#define CLI_MAX_HISTORY         (3)         //最大支持历史记录
#define CLI_MAX_HISTORY_SPACE   (8)         //最大支持命令的字符串个数（get card info 是3个字符串）


#define CLI_CMDBUF_MAX_LEN      (64)
#define CLI_CMD_MAX_COMMANDS    (255)
#define CLI_CMD_MAX_LEN         (25)
#define CLI_HELP_MAX_LEN        (48)

/* User command should return these value below */
#define CLI_NONE                  (0)
#define CLI_SUCCESS               (1)
#define CLI_FAIL                  (2)
#define CLI_PARAMETER_ERROR       (3)
#define CLI_PORTNUM_ERROR         (4)
#define CLI_PORT_DISABLE          (5)
#define CLI_MODULE_NOT_INSERT     (6)
#define CLI_NOT_SUPPORT_FUNCTION  (7)
#define CLI_UNRECONGNIZED_MODULE  (8)
#define CLI_LINENUM_ERROR          (9)


/* if max commands less than 255, use UI8_T to save memory */
#if (CLI_CMD_MAX_COMMANDS <= 255)
  #define CLI_CMD_INDEX_T       UI8_T
#else
  #define CLI_CMD_INDEX_T       UI16_T
#endif

#define CLI_CMD_MAX_ACCOUNT     (1)
#define CLI_USER_MAX_LEN        (16)
#define CLI_PWD_MAX_LEN         (16)

#define CLI_WDOG_FEED_ID		WATCH_DOG_SRC_2

typedef enum
{
    NONE          = 0,
    BOOL          = 1,  /* enable/disable on/off */
    INT           = 2,  
    FLOAT         = 3,
    CHAR          = 4,
    STRING        = 5,
    PORT_ENUM     = 6,
} CLI_CMD_TYPE_T;


typedef enum
{
    HIDE           = 0,
    GUEST          = 1,  /* the cli will print a black line */
    GUEST_         = 2,  /* the cli will print a black line */
    ENGINEER       = 3,  /* the cli will print a black line */
    ENGINEER_      = 4,  /* the cli will print a black line */
    ADMINISTRATOR  = 5,  /* the cli will print success      */
    ADMINISTRATOR_ = 6,  /* the cli will print success      */
    DEBUG          = 7,
    DEBUG_         = 8,
} CLI_ACCOUNT_LEVLE_T;

typedef UI8_T  (*CLI_CMD_EXEC_T)
(
   const UI32_T n_param,
   const UI8_T  *param[]
);

/* user command format */
typedef struct cli_cmd_t
{
    CLI_CMD_INDEX_T index;                     /* command index, start from 1 */
    UI8_T           cmd[CLI_CMD_MAX_LEN + 1];  /* command                     */
    CLI_ACCOUNT_LEVLE_T           level;
    CLI_CMD_TYPE_T                type;
    UI8_T           help[CLI_HELP_MAX_LEN + 1];/* command                     */
    CLI_CMD_EXEC_T  cmd_exec;                  /* execute command function    */
    const  struct cli_cmd_t  *next_cmd;
} CLI_CMD_T;






typedef struct 
{
    UI8_T           index;                       /* command index, start from 1 */
    UI8_T           user[CLI_USER_MAX_LEN + 1];  /* command                     */
    UI8_T           password[CLI_USER_MAX_LEN + 1];/* command                     */
    CLI_ACCOUNT_LEVLE_T           level;
} CLI_ACCOUNT_T;


/* User command should return these value below */
#define CLI_PRINT_NONE        (0)
#define CLI_PRINT_SUCCESS     (1)
#define CLI_PRINT_FAIL        (2)
#define CLI_PRINT_PARM_ERROR  (3)


#if CLI_HISTORY_ENABLE
extern UI8_T           cmd_history_buffer[CLI_MAX_HISTORY][CLI_CMDBUF_MAX_LEN + 1];
extern UI8_T           cmd_history_index;
#endif




extern const  UI8_T  print_success[]             ;
extern const  UI8_T  print_fail[]                ;
extern const  UI8_T  print_parameter_error[]     ;
extern const  UI8_T  print_portnum_error[]       ;
extern const  UI8_T  print_port_disable[]        ;
extern const  UI8_T  print_module_not_inserted[] ;
extern const  UI8_T  print_unknow_error[]        ;
extern const  UI8_T  print_not_support_function[];
extern const  UI8_T  print_uncongnized_module[]  ;
extern const  UI8_T  print_linenum_error[]       ;





/*******************************************************************************
 * FUNCTION NAME:
 *      None
 * DESCRIPTION:
 *      None
 * INPUT:
 *      None
 * OUTPUT:
 *      None
 * RETURN:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      Ver1.00     2007.02.14      Panda Xiong         Create
*******************************************************************************/
extern void cli_MainProcess(void);
extern void cli_UserLogin(void);


/*******************************************************************************
 * CLI Kernel reserved commands
*******************************************************************************/



/*******************************************************************************
 * COPYRIGHT:
 *      None
 * FILE NAME:
 *      None
 * DESCRIPTION:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      Ver1.00     2007.02.14      Panda Xiong         Create
*******************************************************************************/
extern UI8_T CLI_CMD_ClearScreen( const UI32_T index, const UI8_T *data[]);

/*******************************************************************************
 * COPYRIGHT:
 *      None
 * FILE NAME:
 *      None
 * DESCRIPTION:
 *      None
 * NOTES:
 *      None
 * HISTORY:
 *      Ver1.00     2007.02.14      Panda Xiong         Create
*******************************************************************************/
extern UI8_T CLI_CMD_Help( const UI32_T n_param, const UI8_T *param[]);
extern UI8_T CLI_CMD_N_Help( const UI32_T n_param,const CLI_CMD_T   *param);
extern UI8_T CLI_CMD_LOGOUT( const UI32_T n_param, const UI8_T *param[]);

extern UI8_T CLI_CMD_ChangePasswd( const UI32_T index, const UI8_T *data[]);
extern UI8_T CLI_CMD_ChangeLevel( const UI32_T index, const UI8_T *data[]);
extern UI8_T CLI_CMD_AccountFactory( const UI32_T index, const UI8_T *data[]);
extern UI8_T cli_TabMatchCmd( const UI32_T n,  UI8_T *start_addr,const CLI_CMD_T   *cli_cmd_addr,UI8_T **p_cmd_buf);
extern UI8_T SearchUser( const UI8_T *start_addr);
extern UI8_T CheckPwd( const UI8_T index, const UI8_T *start_addr);
extern UI8_T cli_Search_ExecuteCmd( const UI32_T n, const UI8_T *start_addr,const CLI_CMD_T   *cli_cmd_addr);

extern void cli_timeout_count(void);


#endif

