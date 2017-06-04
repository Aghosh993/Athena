#include "board_led.h"

void board_led_init(void)
{
	mibspiInit();
	gioInit();
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case GIO1:
			gioSetBit(MIBSPI_GIO1, 1);
			break;
		case GIO2:
			gioSetBit(MIBSPI_GIO2, 1);
			break;
		case GIO3:
			gioSetBit(MIBSPI_GIO3, 1);
			break;
		case GIO4:
			gioSetBit(MIBSPI_GIO4, 1);
			break;
		case GP_LED:
			gioSetBit(GP_LED_GPIO, 1);
			break;
		case GIO6:
			gioSetBit(GIO6_GPIO, 1);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case GIO1:
			gioSetBit(MIBSPI_GIO1, 0);
			break;
		case GIO2:
			gioSetBit(MIBSPI_GIO2, 0);
			break;
		case GIO3:
			gioSetBit(MIBSPI_GIO3, 0);
			break;
		case GIO4:
			gioSetBit(MIBSPI_GIO4, 0);
			break;
		case GP_LED:
			gioSetBit(GP_LED_GPIO, 0);
			break;
		case GIO6:
			gioSetBit(GIO6_GPIO, 0);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case GIO1:
			gioToggleBit(MIBSPI_GIO1);
			break;
		case GIO2:
			gioToggleBit(MIBSPI_GIO2);
			break;
		case GIO3:
			gioToggleBit(MIBSPI_GIO3);
			break;
		case GIO4:
			gioToggleBit(MIBSPI_GIO4);
			break;
		case GP_LED:
			gioToggleBit(GP_LED_GPIO);
			break;
		case GIO6:
			gioToggleBit(GIO6_GPIO);
			break;
	}
}