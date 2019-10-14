/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "AD5412Driver.h"
#include "KEYDriver.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t FlagLed = 0;
uint8_t ModeSel = 0;
unsigned char buf[4] = {0, 0, 0, 0};	//用于写入AD5412数组

/* USER CODE END Variables */
osThreadId Task1_LEDHandle;
osThreadId Task2_AD5412Handle;
osThreadId Task3_KEYHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void LED_Task(void const * argument);
void AD5412Task(void const * argument);
void LEDTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task1_LED */
  osThreadDef(Task1_LED, LED_Task, osPriorityNormal, 0, 128);
  Task1_LEDHandle = osThreadCreate(osThread(Task1_LED), NULL);

  /* definition and creation of Task2_AD5412 */
  osThreadDef(Task2_AD5412, AD5412Task, osPriorityIdle, 0, 128);
  Task2_AD5412Handle = osThreadCreate(osThread(Task2_AD5412), NULL);

  /* definition and creation of Task3_KEY */
  osThreadDef(Task3_KEY, LEDTask, osPriorityIdle, 0, 128);
  Task3_KEYHandle = osThreadCreate(osThread(Task3_KEY), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_LED_Task */
/**
  * @brief  Function implementing the Task1_LED thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_LED_Task */
void LED_Task(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN LED_Task */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    osDelay(250);
  }
  /* USER CODE END LED_Task */
}

/* USER CODE BEGIN Header_AD5412Task */
/**
* @brief Function implementing the Task2_AD5412 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AD5412Task */
void AD5412Task(void const * argument)
{
  /* USER CODE BEGIN AD5412Task */
//	uint16_t data;

//	data = CurrentToData(IOUT_4_20,20);

//	buf[ 2 ] = 0x56;
//	buf[ 1 ] = 0x00;
//	buf[ 0 ] = 0x01;
//	WriteToAD5422(3, buf);	//Write 551000 到控制寄存器



	buf[2] = 0x55;	//控制寄存器
	buf[1] = 0x10;	//Disable Slew Rate	while selecting the current mode
//	buf[0] = 0x00;				//Selecting the Voltage Mode(0V - 5V)
//	buf[0] = 0x01;				//Selecting the Voltage Mode(0V - 10V)
//	buf[0] = 0x02;				//Selecting the Voltage Mode(-5V - 5V)
//	buf[0] = 0x03;				//Selecting the Voltage Mode(-10V - 10V)
	buf[0] = 0x05;				//Selecting the Current Mode(4mA - 20mA)
//	buf[0] = 0x06;				//Selecting the Current Mode(0mA - 20mA)
//	buf[0] = 0x07;				//Selecting the Current Mode(0mA - 24mA)

	WriteToAD5422(3, buf);	//Write 551000 到控制寄存器

	buf[2] = 0x01;	//数据寄存器
	buf[1] = 0x00;	//
	buf[1] = 0x00;
	WriteToAD5422(3, buf);	//Write 0x010000 to SHIFT REGISTER  to write 0x018000 to DATA REGISTER
	osDelay(1000);


//
//	buf[2] = 0x02;
//	buf[1] = 0x00;
//	buf[0] = 0x01;			    //Read data register
//	WriteToAD5422(3,buf);
  /* Infinite loop */
  for(;;)
  {
	  if( ModeSel == 0 )
	  {
		  //4
		  	  if(FlagLed == 1)
		  	  {
		  		  HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x00;
		  		  buf[0] = 0x00;
		  	  }

		  	  //5
		  	  else if(FlagLed == 2)
		  	  {
		  		  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);	//长亮
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x10;
		  		  buf[0] = 0x00;
		  	  }

		  	  //6
		  	  else if(FlagLed == 3)
		  	  {
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x20;
		  		  buf[0] = 0x00;
		  	  }

		  	  //7
		  	  else if(FlagLed == 4)
		  	  {
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x30;
		  		  buf[0] = 0x00;
		  	  }

		  	  //8
		  	  else if(FlagLed == 5)
		  	  {
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x43;
		  		  buf[0] = 0x34;
		  	  }

		  	  //9
		  	  else if(FlagLed == 6)
		  	  {
		  		  buf[2] = 0x01;
		  		  buf[1] = 0x50;
		  		  buf[0] = 0x00;
		  	  }

		  	  //10
		  	  else if(FlagLed == 7)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0x60;
		  	  		  buf[0] = 0x00;
		  	  	  }

		  	  //11
		  	  else if(FlagLed == 8)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0x70;
		  	  		  buf[0] = 0x00;
		  	  	  }

		  	  //12
		  	  else if(FlagLed == 9)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0x80;
		  	  		  buf[0] = 0x00;
		  	  	  }

		  	  //13
		  	  else if(FlagLed == 10)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0x90;
		  	  		  buf[0] = 0x00;
		  	  	  }

		  	  //14
		  	  else if(FlagLed == 11)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xA0;
		  	  		  buf[0] = 0x00;
		  	  	  }

		  	  //15
		  	  else if(FlagLed == 12)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xB4;
		  	  		  buf[0] = 0xcc;
		  	  	  }

		  	  //16
		  	  else if(FlagLed == 13)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xC4;
		  	  		  buf[0] = 0xcc;
		  	  	  }

		  	  //17
		  	  else if(FlagLed == 14)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xD4;
		  	  		  buf[0] = 0xcc;
		  	  	  }


		  	  //18
		  	  else if(FlagLed == 15)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xE6;
		  	  		  buf[0] = 0x66;
		  	  	  }

		  	  //19
		  	  else if(FlagLed == 16)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xf6;
		  	  		  buf[0] = 0x66;
		  	  	  }

		  	  //20
		  	  else if(FlagLed == 17)
		  	  	  {
		  	  		  buf[2] = 0x01;
		  	  		  buf[1] = 0xff;
		  	  		  buf[0] = 0xff;
		  	  		  FlagLed = 0;
		  	  	  }

	  }


	  if( ModeSel == 1 )
	  {
		  //0V
		  if( FlagLed == 1)
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x00;
			  buf[0] = 0x00;
			  WriteToAD5422(3, buf);
		  }

		  //0.5V
		  else if( FlagLed == 2 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x19;
			  buf[0] = 0x99;
			  WriteToAD5422(3, buf);
		  }

		  //1V
		  else if( FlagLed == 3 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x33;
			  buf[0] = 0x33;
			  WriteToAD5422(3, buf);
		  }

		  //1.5V
		  else if( FlagLed == 4 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x4C;
			  buf[0] = 0xCC;
			  WriteToAD5422(3, buf);
		  }

		  //2V
		  else if( FlagLed == 5 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x66;
			  buf[0] = 0x66;
			  WriteToAD5422(3, buf);
		  }

		  //2.5V
		  else if( FlagLed == 6 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x80;
			  buf[0] = 0x00;
			  WriteToAD5422(3, buf);
		  }

		  //3V
		  else if( FlagLed == 7 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0x99;
			  buf[0] = 0x99;
			  WriteToAD5422(3, buf);
		  }

		  //3.5V
		  else if( FlagLed == 8 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0xB3;
			  buf[0] = 0x33;
			  WriteToAD5422(3, buf);
		  }

		  //4V
		  else if( FlagLed == 9 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0xCC;
			  buf[0] = 0xCC;
			  WriteToAD5422(3, buf);
		  }

		  //4.5V
		  else if( FlagLed == 10 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0xE6;
			  buf[0] = 0x66;
			  WriteToAD5422(3, buf);
		  }

		  //5V
		  else if( FlagLed == 11 )
		  {
			  buf[2] = 0x01;
			  buf[1] = 0xFF;
			  buf[0] = 0xFF;
			  WriteToAD5422(3, buf);
			  FlagLed = 0;
		  }

	  }


	  if( ucKeyValue == KeyNone )
	  {
		  return;
	  }
	  /* 如果按键1按下，选择为0-5V模式 */
	  else if( ( ucKeyValue == KEY_ONE ) && ( FlagLed == 0 ) )
	  {
		  buf[2] = 0x55;	//控制寄存器
		  buf[1] = 0x10;	//Disable Slew Rate	while selecting the current mode
		  buf[0] = 0x00;				//Selecting the Voltage Mode(0V - 5V)
		  WriteToAD5422(3, buf);
		  ModeSel = 1;
	  }

//	  /* 按键2选择 0-10V */
//	  else if( ( ucKeyValue == KEY_TWO ) && ( FlagLed == 0 ) )
//	  {
//		  buf[2] = 0x55;	//控制寄存器
//		  buf[1] = 0x10;	//Disable Slew Rate	while selecting the current mode
//		  buf[0] = 0x01;				//Selecting the Voltage Mode(0V - 10V)
//		  WriteToAD5422(3, buf);
//	  }
//
//	  /* 按键3选择 4-20mA */
//	  else if( ( ucKeyValue == KEY_THREE ) && ( FlagLed == 0 ) )
//	  {
//		  buf[2] = 0x55;	//控制寄存器
//		  buf[1] = 0x10;	//Disable Slew Rate	while selecting the current mode
//		  buf[0] = 0x06;				//Selecting the Current Mode(4mA - 20mA)
//		  WriteToAD5422(3, buf);
//	  }

    osDelay(500);
  }
  /* USER CODE END AD5412Task */
}

/* USER CODE BEGIN Header_LEDTask */
/**
* @brief Function implementing the Task3_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LEDTask */
void LEDTask(void const * argument)
{
  /* USER CODE BEGIN LEDTask */
	uint16_t key;


  /* Infinite loop */
  for(;;)
  {
	  key = ReadKeyStatus();
	  if(key == OnceKeyDown)
	  {
		  FlagLed += 1;
	  }
	  if(key == ContiousKeyDown)
	  {
		  FlagLed = 8;
	  }

	  /* 状态机按键扫描，推荐10ms定时 */
	  KeyProcess();

	  WriteToAD5422(3,buf);		//Write 0x018000 to SHIFT REGISTER  to write 0x018000 to DATA REGISTER


    osDelay(10);
  }
  /* USER CODE END LEDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
