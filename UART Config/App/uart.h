#ifndef UART_H
#define UART_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "gettemperature_ci.h"
#include "cli_command.h"

void receive_data(uint8_t data_rx);
void uart_handle(void);
void uart_init(void);
#endif
