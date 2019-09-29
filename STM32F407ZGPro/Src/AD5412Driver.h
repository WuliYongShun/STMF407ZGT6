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



void WriteToAD5422(unsigned char count,unsigned char *buf);
void ReadFromAD5422(unsigned char count,unsigned char *buf);
//uint16_t CurrentToData(uint8_t curren_type, uint8_t output_data);


#endif /* AD5412DRIVER_H_ */
