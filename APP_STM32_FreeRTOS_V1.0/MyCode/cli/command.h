#ifndef __COMMAND_H__
#define __COMMAND_H__







extern UI8_T CLI_CMD_DEBUG_LEVEL(const UI32_T index, const UI8_T *param[]);





UI8_T CLI_CMD_SystemRestart(const UI32_T index, const UI8_T *data[]);

UI8_T CLI_DEBUG_TASK_INFO(const UI32_T index, const UI8_T *data[]);

UI8_T CLI_CMD_DEBUG_HEAP_REMAIN(const UI32_T n_param, const UI8_T *param[]);


#endif
