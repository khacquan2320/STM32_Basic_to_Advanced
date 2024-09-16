#ifndef CLI_TYPESS_H
#define CLI_TYPESS_H
#include <stdint.h>

typedef void(*cli_command_func_t)(char **argv,uint8_t argv_num);

typedef struct
{
	cli_command_func_t function;
	char 								*help;
}cli_command_info_t;

typedef struct
{
	const char 		*name;
	const cli_command_info_t *command_infor;
}cli_command_entry_t;
#endif

