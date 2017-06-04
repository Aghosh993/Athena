#ifndef BOARD_LED_H
#define BOARD_LED_H		1

#include "hal_common_includes.h"

#define MIBSPI_GIO1	mibspiPORT3, PIN_SOMI
#define MIBSPI_GIO2	mibspiPORT3, PIN_SIMO
#define MIBSPI_GIO3	mibspiPORT3, PIN_CLK
#define MIBSPI_GIO4	mibspiPORT3, PIN_ENA

#define GIO6_GPIO	gioPORTB, 1U
#define GP_LED_GPIO	gioPORTB, 2U

#define LED1 GIO1
#define LED2 GIO3

typedef enum {
	GIO1,
	GIO2,
	GIO3,
	GIO4,
	GP_LED,
	GIO6
} led;

void board_led_init(void);
void board_led_on(led led_id);
void board_led_off(led led_id);
void board_led_toggle(led led_id);

#endif