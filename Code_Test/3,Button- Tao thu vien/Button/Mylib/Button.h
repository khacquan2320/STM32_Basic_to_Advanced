#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"
typedef struct
{
	uint8_t btn_current;
	uint8_t btn_last;
	uint8_t btn_filter;
	uint8_t is_debouncing;
	uint32_t time_deboune;
	uint32_t time_start_press;
	uint8_t is_press_timeout;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typdef;
	
void button_handle(Button_Typdef *ButtonX);
void button_init(Button_Typdef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif
