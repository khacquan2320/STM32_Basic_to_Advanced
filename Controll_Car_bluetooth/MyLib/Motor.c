#include "Motor.h"
#include "Pwm.h"
void Motor_control(Motor_Typedef *motor,MotorState state, uint8_t speed)
{
	switch(state)
	{
		case Motor_stop:
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,0);
			pwm_set_duty(motor->tim, motor->tim_chanel ,0);
			break; 	
		case Motor_Cw:
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,0);
			pwm_set_duty(motor->tim, motor->tim_chanel,speed);
			break;
		case Motor_Ccw:
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,1);
			pwm_set_duty(motor->tim, motor->tim_chanel,100-speed);
			break;
	}
}
void motor_init(Motor_Typedef *motor, GPIO_TypeDef *io_port,
								uint16_t io_pin,TIM_HandleTypeDef *tim, uint32_t tim_chanel)
{
	motor->io_port = io_port;
	motor->io_pin = io_pin;
	motor->tim = tim;
	motor->tim_chanel = tim_chanel;
	HAL_TIM_PWM_Start(motor->tim,motor->tim_chanel);
}