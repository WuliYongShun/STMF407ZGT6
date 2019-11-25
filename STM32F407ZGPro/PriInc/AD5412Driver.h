/*
 * AD5412Driver.h
 *
 *  Created on: 2019年9月29日
 *      Author: S
 */

#ifndef AD5412DRIVER_H_
#define AD5412DRIVER_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 单片机引脚宏定义 */
#define LATCH_Pin GPIO_PIN_4
#define LATCH_GPIO_Port GPIOD
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOD
#define SDI_Pin GPIO_PIN_6
#define SDI_GPIO_Port GPIOD
#define SDO_Pin GPIO_PIN_7
#define SDO_GPIO_Port GPIOD

/* 预处理宏定义，选择芯片不可以同时定义 */
#define AD5412
//#define AD5422


/* 输出电流类型：1、4-20mA，2、0-20mA，3、0-24mA */
enum IoutType
{
	IOUT_4_20,
	IOUT_0_20,
	IOUT_0_24
};

/* 输出电压类型：1、0-5V，2、0-10V */
enum VoutType
{
	VOUT_0_5,
	VOUT_0_10,
};



void WriteToAD5422(unsigned char count,unsigned char *buf);
void ReadFromAD5422(unsigned char count,unsigned char *buf);
uint16_t CurrentToData(uint8_t curren_type, uint8_t output_data);
uint16_t VoltageToData( uint8_t vol_type, uint8_t output_data );




#ifdef __cplusplus
}
#endif
#endif /* AD5412DRIVER_H_ */
