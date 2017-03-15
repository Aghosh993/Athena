#include "board_led.h"

void board_led_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitTypeDef a;

	a.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	a.GPIO_Mode = GPIO_Mode_OUT;
	a.GPIO_PuPd = GPIO_PuPd_NOPULL;
	a.GPIO_OType = GPIO_OType_PP;
	a.GPIO_Speed = GPIO_Speed_Level_2;

	GPIO_Init(GPIOE, &a);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
			break;
		case LED2:
			GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_RESET);
			break;
		case LED2:
			GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			switch(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8))
			{
				case Bit_SET:
					GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_RESET);
					return;
				case Bit_RESET:
					GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
					return;
			}
			break;
		case LED2:
			switch(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_9))
			{
				case Bit_SET:
					GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
					return;
				case Bit_RESET:
					GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
					return;
			}
			break;
	}
}