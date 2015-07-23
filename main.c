#include <stdint.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_dbgmcu.h>
#include <stdio.h>
#include <systems.h>

RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{  
	uint32_t i = 0;

	RCC_GetClocksFreq( &RCC_Clocks );

	ConfigureLED(); LED_ON;

	/* SysTick end of count event each 10ms */
//	SysTick_Config( RCC_Clocks.HCLK_Frequency / 100);

//	printf( "Operating at %dHz\n", RCC_Clocks.HCLK_Frequency );
	while(1)
	{
	}
}

void TimingDelay_Decrement()
{
}


