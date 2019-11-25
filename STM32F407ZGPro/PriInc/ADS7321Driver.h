/*
 * ADS7321Driver.h
 *
 *  Created on: 2019年11月18日
 *      Author: S
 */

#ifndef ADS7321DRIVER_H_
#define ADS7321DRIVER_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 管脚宏定义 */
#define ADS7321_SCK_Pin GPIO_PIN_3
#define ADS7321_SCK_GPIO_Port GPIOB
#define ADS7321_SDO_Pin GPIO_PIN_4
#define ADS7321_SDO_GPIO_Port GPIOB
#define ADS7321_SDI_Pin GPIO_PIN_5
#define ADS7321_SDI_GPIO_Port GPIOB
#define ADS7321_CS_Pin GPIO_PIN_8
#define ADS7321_CS_GPIO_Port GPIOB


/* add the header file here */
#define	CONTROL_REGISTER	0x8000
#define	RANGE_REGISTER		0xA000

#define	CONVENTION		0x0000

/*-----------------reg0(CONTROL_REGISTER)----------------*/
#define	ADD0_VIN0		0x0
#define	ADD0_VIN1     	0x400
#define	FULL_DIFFERENTIAL	0x200
#define	PSEUDO_DIFFERENTIAL	0x100
#define	SINGLE_ENDED		0x0
#define	NORMAL_MODE			0x0
#define	AUTOSTANDBY_MODE	0x40
#define	AUTOSTANDDOWN_MODE	0x80
#define	FULL_SHUTDOWN_MODE	0xB0
#define	SEQUENCER_USED		0x08
#define	SEQUENCER_NOT_USED		0x0
#define	TWOS_COMPLEMENT_CODING	0x0
#define	STRAIGHT_BINARY			0x20
#define	INTERNAL_REF			0x10
#define	EXTERNAL_REF			0x0

/*-----------------reg1(RANGE_REGISTER)----------------*/
#define	VIN0_10V			0x0
#define	VIN0_5V				0x800
#define	VIN0_2_5V			0x1000
#define	VIN0_0_10V			0x1800
#define	VIN1_10V			0x0
#define	VIN1_5V				0x80
#define	VIN1_2_5V			0x100
#define	VIN1_0_10V			0x180




uint16_t AD7321_Read_Wite( uint16_t sendData );



#ifdef __cplusplus
}
#endif

#endif /* ADS7321DRIVER_H_ */
