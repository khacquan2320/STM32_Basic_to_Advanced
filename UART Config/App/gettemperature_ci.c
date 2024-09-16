#include "gettemperature_ci.h"
#include <stdlib.h>
void gettempearture(char **argv, uint8_t arg_num )
{
	if(arg_num < 2)
	{
			response_print("don't enough arg, arg = %d", arg_num);
			return;
	}
	if(arg_num > 2)
	{
		response_print("too much arg,arg = %d", arg_num);
		return;
	}
	uint8_t chanel = atoi(argv[1]);
	response_print("temperature = %f",LM35_Gettemp(chanel));
}
