/*
 * AD5412Deiver.c
 *
 *  Created on: 2019年9月28日
 *      Author: S
 */

#include "AD5412Driver.h"

#define CLR_LATCH()	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, RESET)
#define SET_LATCH()	HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, SET)

#define CLR_SCLK()	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, RESET)
#define SET_SCLK()	HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, SET)

#define CLR_SDI()	HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, RESET)
#define SET_SDI()	HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, SET)

#define GET_SDO()	HAL_GPIO_ReadPin(SDO_GPIO_Port, SDO_Pin)



void AD54X2_Delay(uint32_t Delay)
{
//	HAL_Delay(Delay);
	while (Delay > 0) Delay--;
}

void WriteToAD5422(unsigned char count,unsigned char *buf)
{
	unsigned char ValueToWrite = 0;
    unsigned char i = 0;
	unsigned char j = 0;

	/* 使能芯片 */
	CLR_LATCH();

	/* 一次发送缓冲区中count个数据 */
	for(i = count; i > 0; i--)
 	{
	 	ValueToWrite =	*(buf + i - 1);

		/* 一次发8位 */
		for(j=0; j<8; j++)
		{
			CLR_SCLK();

			/* 从8位高字节开始发送，单片机IO输出响应电平 */
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_SDI();	    //Send one to SDIN pin of AD5422
			}
			else
			{
				CLR_SDI();	    //Send zero to SDIN pin of AD5422
			}

			AD54X2_Delay(1);

			/* 时钟搞定平准备下一位 */
			SET_SCLK();
			AD54X2_Delay(1);
			ValueToWrite <<= 1;	//依次发送下一位
		}
	}

	/* 拉低时钟，时钟默认为低电平 */
	CLR_SCLK();
	AD54X2_Delay(1);

	/* 失能芯片 */
	SET_LATCH();
	AD54X2_Delay(20);
}

void ReadFromAD5422(unsigned char count,unsigned char *buf)
{
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char TempData = 0;
	unsigned char RotateData = 0;

	/* 使能芯片 */
	CLR_LATCH();

	/* 发送count个数据 */
	for(j = count; j > 0; j--)
	{
		/* 从低字节开始读取数据 */
		for(i = 0; i < 8; i++)
		{
			CLR_SCLK();
			RotateData <<= 1;
			AD54X2_Delay(1);

			/* 读取数据前向芯片寄存器发送一个0 */
			CLR_SDI();

			/* 依次读取数据位 */
			TempData = GET_SDO();
			SET_SCLK();

			if(TempData == 1)
			{
				RotateData |= 1;
			}
			AD54X2_Delay(1);
		}

		/* 数据缓存区依次写入数据 */
		*(buf + j - 1) = RotateData;
	}
	CLR_SCLK();
	AD54X2_Delay(1);

	/* 失能芯片 */
	SET_LATCH();
	AD54X2_Delay(20);
}


//uint16_t CurrentToData(uint8_t current_type, uint8_t output_data)
//{
//	uint16_t Data;
//
//#ifdef	AD5412
//	switch(current_type)
//	{
//	case IOUT_4_20:
//		Data = ((output_data - 4) * 4096) / 16;
//		break;
//
//	case IOUT_0_20:
//		Data = ((output_data) * 4096) / 20;
//		break;
//
//	case IOUT_0_24:
//		Data = ((output_data) * 4096) / 24;
//		break;
//
//	default:
//		break;
//	}
//#endif
//
//#ifdef AD5422
//	switch(current_type)
//		{
//		case IOUT_4_20:
//			Data = ((output_data - 4) * 65536) / 16;
//			break;
//
//		case IOUT_0_20:
//			Data = ((output_data) * 65536) / 20;
//			break;
//
//		case IOUT_0_24:
//			Data = ((output_data) * 65536) / 24;
//			break;
//
//		default:
//			break;
//		}
//#endif
//	return Data;
//}
