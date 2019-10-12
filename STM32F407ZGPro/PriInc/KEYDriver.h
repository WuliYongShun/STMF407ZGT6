/*
 * KEYDriver.h
 *
 *  Created on: 2019年9月29日
 *      Author: S
 */

#ifndef KEYDRIVER_H_
#define KEYDRIVER_H_

#ifdef   KEY_DRIVER
#define  KEY_DRIVER_EXT
#else
#define  KEY_DRIVER_EXT  extern
#endif

#include "stm32f4xx_hal.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_NONE     0      //没有按键按下
#define KEY_ONE   	 0x01   //按键一
#define KEY_TWO		 0x02 	//按键二
#define KEY_THREE    0x04   //按键三

KEY_DRIVER_EXT uint8_t ucKeyValue;


typedef enum
{
	NoKeyDown = 0,
	KeySureDown,
	OnceKeyDown,
	ContiousKeyDown
}StateStatus;

enum
{
	KeyWake,
	Key1,
	Key2,
	Key3,
	KeyNone
};

KEY_DRIVER_EXT StateStatus ReadKeyStatus( void );
KEY_DRIVER_EXT void KeyProcess( void );


#ifdef __cplusplus
}
#endif
#endif /* KEYDRIVER_H_ */
