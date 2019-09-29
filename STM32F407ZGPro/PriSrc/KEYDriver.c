/*
 * KYEDriver.c
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: S
 */

#include "KEYDriver.h"

#define ReadWake()	HAL_GPIO_ReadPin(K_WakeUp_GPIO_Port, K_WakeUp_Pin)
#define ReadKey1()	HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin)
#define ReadKey2()  HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)
#define ReadKey3()	HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin)

static uint8_t GetKey(void)
{
	if(ReadWake() == 1)
	{
		return KeyWake;
	}

	if(ReadKey1() == 0)
	{
		return Key1;
	}

	if(ReadKey2() == 0)
	{
		return Key2;
	}

	if(ReadKey3() == 0)
	{
		return Key3;
	}

	return KeyNone;
}


StateStatus ReadKeyStatus(void)
{
	StateStatus state = NoKeyDown;
	static int TimeCount = 0;
	int KeyPress = ReadKey1();
	StateStatus KeyReturn = NoKeyDown;

	switch(state)
	{
	case NoKeyDown:
		if(!KeyPress)
		{
			state = KeySureDown;
		}
		break;

	case KeySureDown:
		if(!KeyPress)
		{
			state = OnceKeyDown;
			TimeCount = 0;

		}
		else
		{
			state = NoKeyDown;
		}
		break;

	case OnceKeyDown:
		if(KeyPress)
		{
			state = NoKeyDown;
			KeyReturn = OnceKeyDown;
		}
		else if(++TimeCount > 100)
		{
			state = ContiousKeyDown;
			TimeCount = 0;
			KeyReturn = ContiousKeyDown;
		}
		break;

	case ContiousKeyDown:
		if(KeyPress)
		{
			state = NoKeyDown;
			KeyReturn = NoKeyDown;
		}
		else if(++TimeCount > 50)
		{
			KeyReturn = ContiousKeyDown;
			TimeCount = 0;
		}
		else
		{
			KeyReturn = NoKeyDown;

		}
		break;
	}
	return KeyReturn;
}
