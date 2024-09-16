#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H
#include "stm32f1xx_hal.h"
#include <string.h>
#include "response_ci.h"
#include "gettemperature_ci.h"

void cli_command_excute(char* uart_buff , uint8_t leng);

#endif
