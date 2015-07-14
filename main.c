#include <stdint.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_dbgmcu.h>
#include <stdio.h>
#include <systems.h>

RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint8_t i = 0;

	RCC_GetClocksFreq( &RCC_Clocks );

	/* Enable the GPIO_LED Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	printf( "Operating at %dHz\n", RCC_Clocks.HCLK_Frequency );

	/* SysTick end of count event each 10ms */
	//SysTick_Config( RCC_Clocks.HCLK_Frequency / 100);

	while(1)
	{
	//	printf( "Hello %d\n", i++ );
		GPIOB->ODR ^= GPIO_Pin_8;
		_delay_us(1000000);
	}
}


void TimingDelay_Decrement()
{
	//GPIOB->ODR ^= GPIO_Pin_8;
}


