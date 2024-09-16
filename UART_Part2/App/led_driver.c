#include "led_driver.h"
#include "stm32f1xx_hal.h"
void control_led(int index, int sta)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0<<index,(GPIO_PinState)sta);
}