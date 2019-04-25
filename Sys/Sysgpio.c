#include "Sysgpio.h"

void gpio_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	SET_GPIO_OUT(LED1);
	SET_GPIO_OUT(LED2);
	SET_GPIO_OUT(LED3);
	SET_GPIO_OUT(LED4);
}

void Set_GPIO_PIN(GPIO_TypeDef *gpio, u16 nPin,u32 mode,u32 speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	HAL_GPIO_WritePin(gpio, nPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = nPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(gpio, &GPIO_InitStruct);

}















