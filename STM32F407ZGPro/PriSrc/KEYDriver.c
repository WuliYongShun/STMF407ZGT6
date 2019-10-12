/*
 * KYEDriver.c
 *
 *  Created on: 2019��9��29��
 *      Author: S
 */

#define KEY_DRIVER
#include "KEYDriver.h"

#define KEY_KEEP_TIME               3      //����״̬�ȶ�ʱ�� x10ms

#define ReadWake()	HAL_GPIO_ReadPin(K_WakeUp_GPIO_Port, K_WakeUp_Pin)
#define ReadKey1()	HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin)
#define ReadKey2()  HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)
#define ReadKey3()	HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin)

//static uint8_t GetKey(void)
//{
//	if(ReadWake() == 1)
//	{
//		return KeyWake;
//	}
//
//	if(ReadKey1() == 0)
//	{
//		return Key1;
//	}
//
//	if(ReadKey2() == 0)
//	{
//		return Key2;
//	}
//
//	if(ReadKey3() == 0)
//	{
//		return Key3;
//	}
//
//	return KeyNone;
//}


StateStatus ReadKeyStatus( void )
{
	static StateStatus state = NoKeyDown;
	static int TimeCount = 0;
	int KeyPress = ReadWake( );
	StateStatus KeyReturn = NoKeyDown;

	switch( state )
	{
	case NoKeyDown:
		if( KeyPress )
		{
			state = KeySureDown;
		}
		break;

	case KeySureDown:
		if( KeyPress )
		{
			state = OnceKeyDown;
			TimeCount = 0;

		}
		else
		{
			state = NoKeyDown;
		}
		break;

		/* �������� */
	case OnceKeyDown:
		if( !KeyPress )
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

		/* �������� */
	case ContiousKeyDown:
		if(!KeyPress)
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
		
	default:
		break;
	}
	return KeyReturn;
}

/* ���������ϳ�һ���ַ� */
uint8_t ReadKeyStu( void )
{
    uint8_t KeyData = KEY_NONE;

	if( ReadKey1( ) == 0 )
	{
	    KeyData |= KEY_ONE;
	}
	else if( ReadKey2( ) == 0 )
	{
	    KeyData |= KEY_TWO;
	}
	else if( ReadKey3( ) == 0 )
	{
	     KeyData |= KEY_THREE;
	}

	return KeyData;
}

/* ����״̬������ */
void KeyProcess( void )
{
	static uint8_t Key1, Key2;
	static uint16_t Count = 0;

	Key1  = ReadKeyStu( );

	if( Key1 == Key2 )
	{
		Count++;
		if( Count ==  KEY_KEEP_TIME )
		{
			if( Key1 != KEY_NONE )
			{
			    ucKeyValue = Key1;
			}
		}

		if( Count > KEY_KEEP_TIME )
		{
			Count = KEY_KEEP_TIME + 1;
		}
	}
	else
	{
		Count = 0;
		Key2 = Key1;
	}
}

