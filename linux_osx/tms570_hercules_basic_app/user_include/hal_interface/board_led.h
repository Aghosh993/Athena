#ifndef BOARD_LED_H
#define BOARD_LED_H		1

#include "hal_common_includes.h"

// Red LED on interface board:
// #define MIBSPI_GIO1	mibspiPORT3, PIN_SOMI
// Green LED on interface board:
// #define MIBSPI_GIO2	mibspiPORT3, PIN_CLK

typedef enum {
	LED1,
	LED2
} led;

void board_led_init(void);
void board_led_on(led led_id);
void board_led_off(led led_id);
void board_led_toggle(led led_id);

#endif