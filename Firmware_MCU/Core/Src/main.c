/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "SX1231_APP.h"

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
uint16_t ADC_Val[4];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int i, a, b, c, d, uart_rx_invalid;
	uint8_t bfr[SX1231_PayloadLength];
	__IO uint8_t UART_Buf[24];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	LL_SPI_Enable(SPI1);
	
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 4);
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA));
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)ADC_Val);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	
	LL_ADC_Enable(ADC1);
	LL_ADC_StartCalibration(ADC1);
	while(LL_ADC_IsCalibrationOnGoing(ADC1));

	LL_ADC_REG_SetDMATransfer(ADC1,LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
	
	
	
	
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, 24);
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_5, LL_USART_DMA_GetRegAddr(USART1));
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)UART_Buf);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
	LL_USART_EnableDMAReq_RX(USART1);
	
	


	
	//printf("%d", sizeof(float));
	LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
	
	SX1231_Init_Primary();
  while (!SX1231_IsActiveFlag_ModeReady(&SX1231_Primary))
  {
    //printf("wait\r\n");
  }
	
	

  
  while(1)
	{
		if(LL_DMA_IsActiveFlag_TC5(DMA1))
		{
			uart_rx_invalid = 0;
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
			LL_DMA_ClearFlag_TC5(DMA1);
			LL_USART_ClearFlag_IDLE(USART1);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, 24);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
			
			UART_Buf[15] = 0;
		}
		else
		{
			uart_rx_invalid++;
			if(uart_rx_invalid > 10)
			{
				uart_rx_invalid = 0;
				LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
				LL_USART_DisableDMAReq_RX(USART1);
				LL_USART_EnableDMAReq_RX(USART1);
				LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, 24);
				LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
				UART_Buf[0] = 9;
				UART_Buf[1] = 3;
				UART_Buf[2] = 2;
				UART_Buf[3] = 7;
				UART_Buf[4] = 10;
				UART_Buf[5] = 4;
			}
		}
    
		a = (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_8) ? 0x01 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_15) ? 0x02 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_3) ? 0x04 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_4) ? 0x08 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_5) ? 0x10 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_6) ? 0x20 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_7) ? 0x40 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_8) ? 0x80 : 0 ) ;
		
		b = (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_9) ? 0x01 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_10) ? 0x02 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_11) ? 0x04 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_14) ? 0x08 : 0 ) +
				(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_15) ? 0x10 : 0 ) ;
		
		
		//printf("%02x %02x %03x %03x %03x %03x\r\n", a, b, ADC_Val[0], ADC_Val[1], ADC_Val[2], ADC_Val[3]);
		bfr[0] = 0x23;
		bfr[1] = 0x33;
		bfr[2] = a;
		bfr[3] = b;
		bfr[4] = ADC_Val[0] >> 8;
		bfr[5] = ADC_Val[0] & 0xff;
		bfr[6] = ADC_Val[1] >> 8;
		bfr[7] = ADC_Val[1] & 0xff;
		bfr[8] = ADC_Val[2] >> 8;
		bfr[9] = ADC_Val[2] & 0xff;
		bfr[10] = ADC_Val[3] >> 8;
		bfr[11] = ADC_Val[3] & 0xff;
		
		bfr[12] = UART_Buf[0];
		bfr[13] = UART_Buf[1];
		bfr[14] = UART_Buf[2];
		bfr[15] = UART_Buf[3];
		bfr[16] = UART_Buf[4];
		bfr[17] = UART_Buf[5];
		
		bfr[18] = UART_Buf[6];
		bfr[19] = UART_Buf[7];
		bfr[20] = UART_Buf[8];
		bfr[21] = UART_Buf[9];
		bfr[22] = UART_Buf[10];
		bfr[23] = UART_Buf[11];
		
		bfr[24] = UART_Buf[12];
		bfr[25] = UART_Buf[13];
		bfr[26] = UART_Buf[14];
		bfr[27] = UART_Buf[15];
		bfr[28] = UART_Buf[16];
		bfr[29] = UART_Buf[17];
		
		bfr[30] = UART_Buf[18];
		bfr[31] = UART_Buf[19];
		bfr[32] = UART_Buf[20];
		bfr[33] = UART_Buf[21];
		bfr[34] = UART_Buf[22];
		bfr[35] = UART_Buf[23];
		
		printf("kP = %f, kI = %f, kD = %f\r\n", (float)bfr[12] + (float)bfr[13] / 10, (float)bfr[14] + (float)bfr[15] / 10, (float)bfr[16] + (float)bfr[17] / 10);
    
		SX1231_Primary_TransmitPacket(bfr);
  }
	
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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_3);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(24000000);
  LL_SetSystemCoreClock(24000000);
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_8);
}

/* USER CODE BEGIN 4 */
int fputc(int ch, FILE* f)
{
	LL_USART_TransmitData8(USART1, (unsigned char)ch);
	while(!LL_USART_IsActiveFlag_TXE(USART1));
	return ch;
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
