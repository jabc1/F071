#include "sys_clock.h"
#include "Sysgpio.h"
#include "Sysuart.h"
#include "Delay.h"
#include "MyTask.h"
#include "Memory.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	delay_init(48-1);
	gpio_init();
	Init_memory();
	MX_DMA_Init();
	MX_USART1_UART_Init();//wifi
	MX_USART3_UART_Init();//232
	start_system();

}










