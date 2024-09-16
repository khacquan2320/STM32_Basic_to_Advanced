#ifndef MOTOR_H
#define MOTOR_H
#include "stm32f1xx.h"
typedef enum 
{	
	Motor_stop,
	Motor_Cw,         //cung chieu 
	Motor_Ccw,				//nguoc chieu
	
}MotorState;


typedef struct
{
	GPIO_TypeDef *io_port;
	uint16_t io_pin;
	TIM_HandleTypeDef* tim;
	uint32_t tim_chanel;
	MotorState motorstate;
	uint8_t speed;
}Motor_Typedef;
void Motor_control(Motor_Typedef *motor,MotorState state, uint8_t speed);
void motor_init(Motor_Typedef *motor, GPIO_TypeDef *io_port,
								uint16_t io_pin,TIM_HandleTypeDef *tim, uint32_t tim_chanel);

#endif