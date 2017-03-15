#include "board_led.h"

void board_led_init(void)
{
	// RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef a;

	a.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	a.GPIO_Mode = GPIO_Mode_OUT;
	a.GPIO_PuPd = GPIO_PuPd_NOPULL;
	a.GPIO_OType = GPIO_OType_PP;
	a.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(GPIOD, &a);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
			break;
		case LED2:
			GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
			break;
		case LED2:
			GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			switch(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_12))
			{
				case Bit_SET:
					GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
					return;
				case Bit_RESET:
					GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
					return;
			}
			break;
		case LED2:
			switch(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_13))
			{
				case Bit_SET:
					GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET);
					return;
				case Bit_RESET:
					GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
					return;
			}
			break;
	}
}