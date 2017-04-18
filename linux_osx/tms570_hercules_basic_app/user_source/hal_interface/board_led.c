#include "board_led.h"

void board_led_init(void)
{
	gioInit();
	gioSetBit(gioPORTB, 1, 0);
	gioSetBit(gioPORTB, 2, 0);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			gioSetBit(gioPORTB, 1, 1);
			break;
		case LED2:
			gioSetBit(gioPORTB, 2, 1);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			gioSetBit(gioPORTB, 1, 0);
			break;
		case LED2:
			gioSetBit(gioPORTB, 2, 0);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			gioToggleBit(gioPORTB, 1);
			break;
		case LED2:
			gioToggleBit(gioPORTB, 2);
			break;
	}
}