/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 12:55:42
 */
#include "stm32f10x.h"
#include "Delay.h"

int main(void)
{
	/*使用PA10测试*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_MODE10;	// 通用推挽输出 50MHz
	// 默认熄灭 LED低电平点亮，高电平熄灭
	GPIOA->BSRR |= GPIO_BSRR_BS10;

	while(1)
	{
		GPIOA->BRR |= GPIO_BRR_BR10;	// 点亮 LED
		Delay_ms(1000);
		GPIOA->BSRR |= GPIO_BSRR_BS10;	// 熄灭 LED
		Delay_ms(1000);
	}
}

