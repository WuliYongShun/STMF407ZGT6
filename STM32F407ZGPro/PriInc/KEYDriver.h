/*
 * KEYDriver.h
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: S
 */

#ifndef KEYDRIVER_H_
#define KEYDRIVER_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


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

StateStatus ReadKeyStatus(void);


#ifdef __cplusplus
}
#endif
#endif /* KEYDRIVER_H_ */
