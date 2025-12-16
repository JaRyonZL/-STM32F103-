#include "stm32f10x.h"

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
		GPIOC->ODR ^= GPIO_ODR_ODR10;           // 翻转 LED
        for(volatile int i = 0; i < 500000; i++);
	}
}

