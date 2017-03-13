#include "board_led.h"

void board_led_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, GPIO_PIN_0);
			break;
		case LED2:
			// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			ROM_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, 0);
			break;
		case LED2:
			// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			// HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
			break;
		case LED2:
			// HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
			break;
	}
}