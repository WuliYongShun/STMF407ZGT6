/*
 * ADS7321Driver.c
 *
 *  Created on: 2019��11��18��
 *      Author: S
 */
#include "ADS7321Driver.h"

#define CLR_CS( )	HAL_GPIO_WritePin(ADS7321_CS_GPIO_Port, ADS7321_CS_Pin, RESET)
#define SET_CS( )	HAL_GPIO_WritePin(ADS7321_CS_GPIO_Port, ADS7321_CS_Pin, SET)

#define CLR_SCLK( )	HAL_GPIO_WritePin(ADS7321_SCK_GPIO_Port, ADS7321_SCK_Pin, RESET)
#define SET_SCLK( )	HAL_GPIO_WritePin(ADS7321_SCK_GPIO_Port, ADS7321_SCK_Pin, SET)

#define CLR_SDI( )	HAL_GPIO_WritePin(ADS7321_SDI_GPIO_Port, ADS7321_SDI_Pin, RESET)
#define SET_SDI( )	HAL_GPIO_WritePin(ADS7321_SDI_GPIO_Port, ADS7321_SDI_Pin, SET)

#define GET_SDO( )	HAL_GPIO_ReadPin(ADS7321_SDO_GPIO_Port, ADS7321_SDO_Pin)


void delay( uint16_t time )
{
	uint16_t i;
	for( i = 0; i < time; i++ ){ }
}

uint16_t AD7321_Read_Wite( uint16_t sendData )
{
	uint16_t num;

	uint16_t receiveData;


	SET_CS( );
	CLR_CS( );		//����Ƭѡ

	for( num = 0; num < 16; num++ )
	{
		SET_SCLK( );		//����ʱ��
		receiveData = ( receiveData << 1 );		//������������һλ

		/* �Ӹ�λ���λ���� */
		if( ( sendData & 0x8000 ) == 0x8000 )
		{
			SET_SDI( );
		}
		else
		{
			CLR_SDI( );
		}

		/* �ӵ�λ����λ�������� */
		if( GET_SDO( ) == 1 )
		{
			receiveData |= 0x0001;
		}
		else
		{
			receiveData &= ~0x0001;
		}
		CLR_SCLK( );		//����ʱ��
		sendData = sendData << 1;

		delay( 1 );
	}

	SET_SCLK( );

	SET_CS( );

	return receiveData;
}

