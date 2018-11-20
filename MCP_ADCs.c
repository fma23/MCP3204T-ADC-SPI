#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "SPI.h"


 uint8_t ADC_Ch0[3]={0};
 uint8_t ADC_Ch1[3]={0};
 uint8_t ADC_Ch2[3]={0};
 uint8_t ADC_Ch3[3]={0};

extern SPI_HandleTypeDef Spi3Handle;

void MCP3204_ReadRequest(uint8_t address)
{
//Read page 15 and page 18 of: https://ww1.microchip.com/downloads/en/DeviceDoc/21298c.pdf
uint8_t RegisterAddressBuff1[3]={0};
	
RegisterAddressBuff1[0]=0x06;
RegisterAddressBuff1[1]= address<<6;
RegisterAddressBuff1[2]=0;	

HAL_GPIO_WritePin(GPIOE, SPI3_CS, GPIO_PIN_RESET); 
	                                                            
while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
        if(address==0x00)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff1[0], &ADC_Ch0[0],3, 1000);
	}
	else if(address==0x01)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff1[0], &ADC_Ch1[0],3, 1000);
	}
	else if(address==0x02)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff1[0], &ADC_Ch2[0],3, 1000);
	}
	else if(address==0x03)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff1[0], &ADC_Ch3[0],3, 1000);
	}
	
	HAL_GPIO_WritePin(GPIOE, SPI3_CS, GPIO_PIN_SET);                  
}
