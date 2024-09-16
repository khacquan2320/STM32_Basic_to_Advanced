#ifndef SERVO_H
#define SERVO_H
#include "stm32f1xx_hal.h"
typedef struct
{
	TIM_HandleTypeDef *htim ;
	uint16_t channel;
	uint8_t angel;
}Servo;
uint8_t servo_read(Servo *sv);
void servo_write(Servo *sv  ,uint8_t angel);
void servo_init(Servo *sv,TIM_HandleTypeDef *htim , uint16_t channel);
#endif