/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef unsigned char byte;

#define WIDTH  (8 * sizeof(byte))

#define POLYNOMIAL 0x07
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
  uint8_t Received[17];
  int q1=0, q2=0, q3=0;

  volatile uint16_t pulse_count; // Licznik impulsow
  volatile uint16_t positions; // Licznik przekreconych pozycji
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
byte CRC8(uint8_t const message[], int nBytes)
{
    byte  remainder = 0;
    for (int byte = 0; byte < nBytes; ++byte)
    {
        remainder ^= message[byte];
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            if ((remainder & 0x80) != 0)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	uint8_t tmp[12];
	uint8_t msg[16];
	uint16_t size = 0;

	uint16_t stmp = sprintf(tmp, "Q%03d %03d %03d", q1, q2, q3);

	byte crc = CRC8(tmp, stmp);

	size = sprintf(msg, "Q%03d %03d %03d %02x\r\n", q1, q2, q3, crc);
	HAL_UART_Transmit(&huart2, msg, size, 50);
	HAL_GPIO_TogglePin(Dioda_GPIO_Port, Dioda_Pin);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	uint8_t Data[17]; // Tablica przechowujaca wysylana wiadomosc.
	uint16_t size = 0; // Rozmiar wysylanej wiadomosci
	char *tmp;
	char crcc[2];

	size = sprintf(Data, "%s", Received);

	if(Data[0] == 'Z' && Data[15] == '\r' && Data[16] == '\n')
	{
		byte crc = CRC8(Data, 12);
		sprintf(crcc, "%02x", crc);

		if(Data[13] == crcc[0] && Data[14] == crcc[1])
		{
			tmp = strtok(Data, " ");
			tmp = tmp+1;
			q1 = atoi(tmp);
			tmp = strtok(NULL, " ");
			q2 = atoi(tmp);
			tmp = strtok(NULL, " ");
			q3 = atoi(tmp);
		}
	}

	HAL_UART_Receive_IT(&huart2, &Received, 17);
	HAL_GPIO_TogglePin(Dioda_GPIO_Port, Dioda_Pin);
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM10_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim10);
  HAL_UART_Receive_IT(&huart2, &Received, 17);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

  htim3.Instance->CNT = 0x0060;
  htim2.Instance->CNT = 0x0060;
  htim1.Instance->CNT = 0x0060;

  int angle=0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  pulse_count = htim3.Instance->CNT; // przepisanie wartosci z rejestru timera
	  positions = pulse_count/4; // zeskalowanie impulsow do liczby stabilnych pozycji walu enkodera

	  angle = (float)360/24 * positions;
	  q3 = angle - 360;

	  pulse_count = htim2.Instance->CNT; 
	  positions = pulse_count/4; 

	  angle = (float)360/24 * positions;
	  q2 = angle - 360;

	  pulse_count = htim1.Instance->CNT; 
	  positions = pulse_count/4; 

	  angle = (float)360/24 * positions;
	  q1 = angle - 360;

	  HAL_Delay(0.5);
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
