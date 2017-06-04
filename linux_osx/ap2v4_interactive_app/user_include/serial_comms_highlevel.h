/*
	File: serial_comms_highlevel.h

	(c) Abhimanyu Ghosh, 2016
 */

#ifndef SERIAL_COMMS_HIGHLEVEL_H_
#define SERIAL_COMMS_HIGHLEVEL_H_	1

#include <stdint.h>
#include "serial_comms_highlevel_hal.h"

#define SERIAL_BUFFER_SIZE	1024U

typedef enum {
	PORT_IDLE,
	PORT_TRANSMITTING_DATA
} serialport_status;

typedef struct {
	uint8_t tx_buffer[SERIAL_BUFFER_SIZE];
	uint8_t rx_buffer[SERIAL_BUFFER_SIZE];

	uint32_t tx_buffer_latest_write_position;
	uint32_t rx_buffer_latest_write_position;

	uint32_t tx_buffer_latest_read_position;
	uint32_t rx_buffer_latest_read_position;

	serialport_desc port_descriptor;
	serialport_status port_state;
} serialport;

/*
	Performs initialization of serial port data structs to known init state:
 */
void serialport_init(serialport *port, serialport_desc pd);

uint32_t serialport_send_data_buffer(serialport *port, uint8_t *data, uint32_t len);
void serialport_send_data_buffer_blocking(serialport *port, uint8_t *data, uint32_t len);

uint32_t serialport_receive_data_buffer(serialport *port, uint8_t *data, uint32_t len);
void serialport_receive_data_buffer_blocking(serialport *port, uint8_t *data, uint32_t len);

void serialport_highlevel_tx_isr(serialport *port);
void serialport_highlevel_rx_isr(serialport *port);

#endif