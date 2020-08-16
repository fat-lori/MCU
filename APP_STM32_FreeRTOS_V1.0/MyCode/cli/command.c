#include "log.h"
#include "cli.h"
#include "command.h"
#include "utl_string.h"



UI8_T CLI_CMD_DEBUG_LEVEL(const UI32_T index, const UI8_T *param[])
{
    UI8_T *pCmd = (UI8_T *)param[0];
    UI8_T byLevel = 0;
    
    pCmd = pCmd + STRTOHEAD(pCmd, 2);
    byLevel = ATOI8(pCmd);
    set_log_level(byLevel);
    
    return CLI_SUCCESS;
}


UI8_T CLI_CMD_SystemRestart( const UI32_T index, const UI8_T *data[])
{
    __set_FAULTMASK(1);
    NVIC_SystemReset();

    return 0;
}




/*

UI8_T CLI_DEBUG_TASK_INFO( const UI32_T index, const UI8_T *data[])
{
	char buff[512] = {0};
	
	

	UTL_VT_PutString("\r\n=================================================\r\n");
	UTL_VT_PutString("name         status priority remaining task_id\r\n");

	vTaskList((char *)&buff);

	UTL_VT_PutString((char*) buff);
	UTL_VT_PutString("\r\n");

	UTL_VT_PutString("\r\nname         running_count     used(%)\r\n");

	vTaskGetRunTimeStats((char *)&buff);

	UTL_VT_PutString((char*) buff);
	UTL_VT_PutString("\r\n");

	
	return 0;
}


UI8_T CLI_CMD_DEBUG_HEAP_REMAIN( const UI32_T n_param, const UI8_T *param[])
{
	size_t t = xPortGetFreeHeapSize();
	print("\r\nFree heap size: %d\r\n",t);
	return CLI_SUCCESS;
}
*/


