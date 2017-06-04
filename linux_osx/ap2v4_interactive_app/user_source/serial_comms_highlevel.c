/*
	File: serial_comms_highlevel.c

	(c) Abhimanyu Ghosh, 2016
 */

#include "serial_comms_highlevel.h"

void serialport_init(serialport *port, serialport_desc pd)
{
	port->port_descriptor = pd;

	uint32_t i = 0U;
	for(i=0U; i<SERIAL_BUFFER_SIZE; ++i)
	{
		port->tx_buffer[i] = (uint8_t)0U;
		port->rx_buffer[i] = (uint8_t)0U;
	}

	port->tx_buffer_latest_write_position = 0U;
	port->tx_buffer_latest_read_position = 0U;

	port->rx_buffer_latest_write_position = 0U;
	port->rx_buffer_latest_read_position = 0U;

	port->port_state = PORT_IDLE;

	serialport_hal_init();
}

uint32_t serialport_send_data_buffer(serialport *port, uint8_t *data, uint32_t len)
{
	uint32_t i = 0U;

	/*
		Atomically store a local copy of the latest position in ring accessed by TX ISR.
		TX ISR uses and increments this, so we must preempt it here and make a local copy...
	 */
	_disable_interrupts();
		uint32_t tx_buffer_latest_read_position_local = port->tx_buffer_latest_read_position;
	_enable_interrupts();

	for(i=0U; i<len; ++i)
	{
		/*
			When start of TX data is one ahead of end, the TX buffer is full:
		 */
		if((port->tx_buffer_latest_write_position + 1U) % SERIAL_BUFFER_SIZE == tx_buffer_latest_read_position_local)
		{
			break;
		}
		else
		{
			port->tx_buffer[(port->tx_buffer_latest_write_position) % SERIAL_BUFFER_SIZE] = data[i];
			++port->tx_buffer_latest_write_position;
			port->tx_buffer_latest_write_position %= SERIAL_BUFFER_SIZE;
		}
	}

	if(port->port_state == PORT_IDLE)
	{
		_disable_interrupts();

			serialport_send_byte(port->port_descriptor, 
									port->tx_buffer[port->tx_buffer_latest_read_position]);
			++port->tx_buffer_latest_read_position;
			port->tx_buffer_latest_read_position %= SERIAL_BUFFER_SIZE;
			port->port_state = PORT_TRANSMITTING_DATA;
			
			serialport_hal_enable_tx_isr(port->port_descriptor);

		_enable_interrupts();
	}
	return i;
}

void serialport_send_data_buffer_blocking(serialport *port, uint8_t *data, uint32_t len)
{
	uint32_t bytes_sent = 0U;
	while(bytes_sent < len)
	{
		bytes_sent += serialport_send_data_buffer(port, &data[bytes_sent], len - bytes_sent);
	}
}

uint32_t serialport_receive_data_buffer(serialport *port, uint8_t *data, uint32_t len)
{
	uint8_t i = 0U;
	/*
		Atomically store a local copy of the latest position in ring accessed by RX ISR.
		RX ISR uses and increments this, so we must preempt it here and make a local copy...
	 */
	_disable_interrupts();
		uint32_t rx_buffer_latest_write_position_local = port->rx_buffer_latest_write_position;
	_enable_interrupts();

	/*
		If the start and end of the data in the ring are at same position, we have an empty RX buffer.
		Therefore, return 0 and don't write to the user-supplied data buffer
	 */
	if(port->rx_buffer_latest_read_position == rx_buffer_latest_write_position_local)
	{
		return 0;
	}
	else
	{
		for(i=0U; i<len; ++i)
		{
			if(port->rx_buffer_latest_read_position == rx_buffer_latest_write_position_local)
			{
				break;
			}
			else
			{
				data[i] = port->rx_buffer[port->rx_buffer_latest_read_position];
				++port->rx_buffer_latest_read_position;
				port->rx_buffer_latest_read_position %= SERIAL_BUFFER_SIZE;
			}
		}
	}
	return i;
}

void serialport_receive_data_buffer_blocking(serialport *port, uint8_t *data, uint32_t len)
{
	uint32_t bytes_recvd = 0U;
	while(bytes_recvd < len)
	{
		bytes_recvd += serialport_receive_data_buffer(port, &data[bytes_recvd], len - bytes_recvd);
	}
}

/*
	Interrupts that handle TX and RX complete events. These are NOT HW-specific and need not be
	modified when porting:
 */

void serialport_highlevel_tx_isr(serialport *port)
{
	/*
		When start and end positions are equal, we have emptied TX buffer by transmitting all bytes:
	 */
	if(port->tx_buffer_latest_read_position == port->tx_buffer_latest_write_position)
	{
		serialport_hal_disable_tx_isr(port->port_descriptor); // Nothing to do, disable TX ints, set port state IDLE
		port->port_state = PORT_IDLE;
	}
	else // Keep shifting out the message...
	{
		serialport_send_byte(port->port_descriptor, 
								port->tx_buffer[port->tx_buffer_latest_read_position]);
		++port->tx_buffer_latest_read_position;
		port->tx_buffer_latest_read_position %= SERIAL_BUFFER_SIZE;
	}
}

void serialport_highlevel_rx_isr(serialport *port)
{
	uint8_t data_received = serialport_receive_byte(port->port_descriptor);

	/*
		When start of RX data is one ahead of end, the RX buffer is full:
	 */
	if((port->rx_buffer_latest_write_position + 1U) % SERIAL_BUFFER_SIZE == port->rx_buffer_latest_read_position)
	{
		return; // Throw incoming data away if receive buffer is full...
	}
	else
	{
		port->rx_buffer[port->rx_buffer_latest_write_position] = data_received;
		++port->rx_buffer_latest_write_position;
		port->rx_buffer_latest_write_position %= SERIAL_BUFFER_SIZE;
	}
}