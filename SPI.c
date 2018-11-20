#include "main.h"
#include "SPI.h"


SPI_HandleTypeDef Spi3Handle;




/**
  * SPI2 error handler
  */
void SPI3Error_Handler(void) 
{
   while(1)
  {
  }
	
 } 

 /**
  * SPI2 Configuration
  */
void SPI3_Config(void){
	
	
	Spi3Handle.Instance               = SPI3;
  
	Spi3Handle.Init.Mode = SPI_MODE_MASTER;
	
  Spi3Handle.Instance               = SPI3;
  Spi3Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // 42MHz/256=167kHz < 400kHz
  Spi3Handle.Init.Direction         = SPI_DIRECTION_2LINES;
  Spi3Handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  Spi3Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  Spi3Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
  Spi3Handle.Init.CRCPolynomial     = 7;
  Spi3Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
  Spi3Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  Spi3Handle.Init.NSS               = SPI_NSS_HARD_OUTPUT;
	Spi3Handle.Init.TIMode            = SPI_TIMODE_DISABLED;

	if(HAL_SPI_Init(&Spi3Handle) != HAL_OK)
  {
    /* Initialization Error */
    SPI3Error_Handler();
  }

}

/**
  * SPI3 Chip Select
  */
void GPIOs_Config(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitTypeDef  GPIO_InitSt;
	
	
	/* Enable both GPIO clock */
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();
	__GPIOE_CLK_ENABLE();
	
	/* SPI3 CHIP Select GPIO pin configuration  */
	GPIO_InitStruct.Pin       = GPIO_PIN_6|GPIO_PIN_8;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;

	HAL_GPIO_Init(SPI3_SCK_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = GPIO_PIN_1;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin       = GPIO_PIN_12;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
	
	