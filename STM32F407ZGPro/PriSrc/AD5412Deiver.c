/*
 * AD5412Deiver.c
 *
 *  Created on: 2019Äê9ÔÂ28ÈÕ
 *      Author: S
 */

#include "AD5412Driver.h"

#define CLR_LATCH()	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, RESET)
#define SET_LATCH()	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, SET)

#define CLR_SCLK()	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, RESET)
#define SET_SCLK()	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, SET)

#define CLR_SDI()	HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, RESET)
#define SET_SDI()	HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, SET)

#define GET_SDI()	HAL_GPIO_ReadPin(SDO_GPIO_Port, SDO_Pin)



void AD54X2_Delayms(uint32_t Delay)
{
//	HAL_Delay(Delay);
	while (Delay >0) Delay--;
}

void WriteToAD5422(unsigned char count,unsigned char *buf)
{
	unsigned char ValueToWrite = 0;
    unsigned char i = 0;
	unsigned char j = 0;

	CLR_LATCH();

	for(i=count; i>0; i--)
 	{
	 	ValueToWrite =	*(buf + i - 1);
		for(j=0; j<8; j++)
		{
			CLR_SCLK();
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_SDI();	    //Send one to SDIN pin of AD5422
			}
			else
			{
				CLR_SDI();	    //Send zero to SDIN pin of AD5422
			}

			AD54X2_Delayms(1);
			SET_SCLK();
			AD54X2_Delayms(1);
			ValueToWrite <<= 1;	//Rotate data

		}

	}
	CLR_SCLK();
	AD54X2_Delayms(1);
	SET_LATCH();
	AD54X2_Delayms(20);
}

