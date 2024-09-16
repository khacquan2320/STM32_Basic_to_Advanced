#include "Car.h"
#include "Motor.h"

Motor_Typedef motor_left;
Motor_Typedef motor_right;

void car_control(CarState car_state, uint8_t speed)
{
	switch(car_state){
		case CAR_STOP_STATE:
			Motor_control(&motor_left,Motor_stop,0);
			Motor_control(&motor_right,Motor_stop,0);
			break;
		case CAR_FORWARD_STATE:
			Motor_control(&motor_left,Motor_Cw,speed);
			Motor_control(&motor_right,Motor_Cw,speed);
			break;
		case CAR_BACKWARD_STATE:
			Motor_control(&motor_left,Motor_Ccw,speed);
			Motor_control(&motor_right,Motor_Ccw,speed);
			break;
		case CAR_LEFT_STATE:
			Motor_control(&motor_left,Motor_stop,0);
			Motor_control(&motor_right,Motor_Ccw,speed);
			break;
		case CAR_RIGHT_STATE:
			Motor_control(&motor_left,Motor_Ccw,speed);
			Motor_control(&motor_right,Motor_stop,0);
			break;
		default:
			break;
	}
}
void car_init(TIM_HandleTypeDef *htim)
{
	motor_init(&motor_left,GPIOB,GPIO_PIN_14,htim,TIM_CHANNEL_1);
	motor_init(&motor_right,GPIOB,GPIO_PIN_15,htim,TIM_CHANNEL_2);
	car_control(CAR_STOP_STATE,0);
}