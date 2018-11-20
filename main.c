/**
  ******************************************************************************
  * Author             : Farid Mabrouk
	* File Name          : main.c
  * Description        : Main program 
  ******************************************************************************/













/* Includes */
#include "main.h"
#include <stdbool.h>


TIM_HandleTypeDef Tim2Handle;
uint32_t uwPrescalerValue=0; ;

void SystemClock_Config(void);
void Error_Handler(void);

int main(void)
{

	
  /*initialize the HAL Library */
  HAL_Init();

	/*System Clock Config */
  SystemClock_Config();
	
	/*SPI Config */
	SPI3_Config();
	GPIOs_Config();
	
	/*TIMER3 Config */
	Timer2_Interrupt_Config();
	
  
	/*wait for interrupts*/
  while (1)
  {
  }

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void Timer2_Interrupt_Config(void)
{
	// TIM2 initialization overflow every 500ms
	// TIM2 by default has clock of 84MHz
  // After HAL_RCC_OscConfig(&RCC_OscInitStruct) is called SystemCoreClock is updated to 525000000
  // and uwPrescalerValue becomes 26250000
	
	
	uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;
  
  /* Set TIM2 instance */
  Tim2Handle.Instance = TIM2;
    
  Tim2Handle.Init.Period = 1600 - 1;    //timer updates every 500ms
  Tim2Handle.Init.Prescaler = uwPrescalerValue;        // 26250000-1
  Tim2Handle.Init.ClockDivision =TIM_CLOCKDIVISION_DIV1;
  Tim2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	if(HAL_TIM_Base_Init(&Tim2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
	/*Start the TIM Base generation in interrupt mode */
  if(HAL_TIM_Base_Start_IT(&Tim2Handle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
}

void Error_Handler(void)
{
  while(1) 
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{

}

#endif
	

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
