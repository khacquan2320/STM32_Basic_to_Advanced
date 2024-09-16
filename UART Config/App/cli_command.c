#include "cli_command.h"
#include "cli_types.h"

const cli_command_info_t *find_command_infor(char *cmd)
{
	
	
	return NULL;
}

void cli_command_excute(char* uart_buff, uint8_t leng)
{
		char *argv [10];
		uint8_t arg_num = 0;
		char *pch ;
		pch = strtok(uart_buff," ");
		while(pch != NULL)
		{
			argv[arg_num] = pch ;
			pch = strtok(NULL," ");
			arg_num++;
		}
		const cli_command_info_t *command_infor = find_command_infor(argv[0]);
		
}
