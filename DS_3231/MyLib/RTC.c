#include "RTC.h"

I2C_HandleTypeDef *rtc_i2c;
uint8_t Decimal2BCD(uint8_t num)
{
	return(num/10)<<4|(num%10);
}
uint8_t BCD2Decimal(uint8_t num)
{
	return (num >>4)*10+(num&0x0F);
}

void RTC_WriteTime(RTC_Typedef *rtc ,DateTime *dt)
{
	uint8_t buff[8];
	buff[0] = 0;
	buff[1] = Decimal2BCD(dt->second);
	buff[2] = Decimal2BCD(dt->min);
	buff[3] = Decimal2BCD(dt->hour);
	buff[4] = Decimal2BCD(dt->day);
	buff[5] = Decimal2BCD(dt->date);
	buff[6] = Decimal2BCD(dt->month);
	buff[7] = Decimal2BCD(dt->year);
	HAL_I2C_Master_Transmit(rtc->rtc_i2c,RTC_ADDR,buff,8,100);
}
void RTC_ReadTime(RTC_Typedef *rtc ,DateTime *dt)
{
	uint8_t buff[7];
	uint8_t add_reg = 0;
	HAL_I2C_Master_Transmit(rtc->rtc_i2c,RTC_ADDR,&add_reg,1,100);
	HAL_I2C_Master_Receive(rtc->rtc_i2c,RTC_ADDR,buff,7,100);
	dt->second = BCD2Decimal(buff[0]);
	dt->min = BCD2Decimal(buff[1]);
	dt->hour = BCD2Decimal(buff[2]);
	dt->day = BCD2Decimal(buff[3]);
	dt->date = BCD2Decimal(buff[4]);
	dt->month = BCD2Decimal(buff[5]);
	dt->year = BCD2Decimal(buff[6]);
}
void RTC_Init(RTC_Typedef *rtc ,I2C_HandleTypeDef *_rtc_i2c)
{
	rtc->rtc_i2c = _rtc_i2c;
}