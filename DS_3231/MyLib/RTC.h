#ifndef RTC_H
#define RTC_H
#include "stm32f1xx.h"
#define RTC_ADDR 0x68<<1
typedef struct
{
	uint8_t second ;
	uint8_t min ;
	uint8_t hour ;
	uint8_t day ;
	uint8_t date ;
	uint8_t month ;
	uint8_t year ;
	
}DateTime;

typedef struct
{
	I2C_HandleTypeDef *rtc_i2c;
	DateTime date_time;
}RTC_Typedef;

void RTC_WriteTime(RTC_Typedef *rtc ,DateTime *dt);
void RTC_ReadTime(RTC_Typedef *rtc , DateTime *dt);
void RTC_Init(RTC_Typedef *rtc ,I2C_HandleTypeDef *_rtc_i2c);
#endif
