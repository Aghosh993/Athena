#include "board_led.h"

void board_led_init(void)
{
	// mibspiInit();
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			// gioSetBit(MIBSPI_GIO1, 1);
			break;
		case LED2:
			// gioSetBit(MIBSPI_GIO2, 1);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			// gioSetBit(MIBSPI_GIO1, 0);
			break;
		case LED2:
			// gioSetBit(MIBSPI_GIO2, 0);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			// gioToggleBit(MIBSPI_GIO1);
			break;
		case LED2:
			// gioToggleBit(MIBSPI_GIO2);
			break;
	}
}