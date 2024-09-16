/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//-------------------------var btn-----------
		uint8_t btn_current = 1;
		uint8_t btn_last = 1;
		uint8_t btn_filter = 1;
		uint8_t is_debounne;
		uint32_t time_deboune;
		uint32_t time_start_press;
		uint8_t is_press_timeout;
		uint8_t test;
//---------------------var led --------------	
typedef enum
{
		Led_off,        
		Led1_blink_1hz,  //---Khoi tao cac trang thai led
		Led2_blink_5hz,
}Ledstatus;
	Ledstatus led_status;		
//------------------------
void btn_pressing_callback()
{
	switch (led_status){
		case Led_off :
			led_status = Led1_blink_1hz;
			break;
		case Led1_blink_1hz :
			led_status = Led2_blink_5hz;
		  break;
		case Led2_blink_5hz :
			led_status = Led_off;
			break;
	}
}
void btn_press_short_callback()
{
	
}
void btn_release_callback()
{
}
void btn_press_timeout_callback()
{
	
}
void led1_blink1hz()
{
	static uint32_t time_led_1 = 0;
	if(HAL_GetTick()- time_led_1 == 500)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		time_led_1 = HAL_GetTick();
	}
}
void led2_blink5hz()
{
	static uint32_t time_led_2 = 0;
	if(HAL_GetTick()- time_led_2 == 100)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
		time_led_2 = HAL_GetTick();
	}
}
void led_off()
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
}
void led_handle()
{
	switch(led_status){
		case Led_off :
			led_off();
			break;
		case Led1_blink_1hz :
			led1_blink1hz();
			break;
		case Led2_blink_5hz :
			led2_blink5hz();
			break;
	}
}
void button_handle()
{
			//---------------------LOc Nhieu-----------------------
		uint8_t sta = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
			if(sta != btn_filter)   // neu nhan nut 
			{
				btn_filter = sta;
				is_debounne = 1;
				time_deboune = HAL_GetTick();
			}
			if(is_debounne && (HAL_GetTick() - time_deboune >= 15 ))
			{ //----------kiem tra xem con nhieu ko---------
				btn_current = btn_filter;
				is_debounne = 0;
			}
			//-------------Xu ly nhan nha-----------------------
			if(btn_current != btn_last)
			{
				if(btn_current == 0) // nhan xuong
				{
					is_press_timeout = 1;
					btn_pressing_callback();
					time_start_press = HAL_GetTick();
					
				}
				else // nha nut
				{
					if(HAL_GetTick() - time_start_press <= 1000)
					{
						btn_press_short_callback();
						is_press_timeout = 0;
					}
					btn_release_callback();
				}
				btn_last = btn_current;
			}
			if(is_press_timeout && (HAL_GetTick() - time_start_press >= 3000))
	  {
		btn_press_timeout_callback();
		is_press_timeout =0;
		}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
		led_status = Led_off;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
