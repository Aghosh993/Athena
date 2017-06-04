/*
	File: serial_comms_highlevel_hal.c

	(c) Abhimanyu Ghosh, 2016
 */

#include "serial_comms_highlevel_hal.h"

/*
	Initializes all required high-level real/virtual serial port HAL drivers:
 */
void serialport_hal_init(void)
{
	sciInit();
	canInit();
	sciEnableNotification(sciREG, SCI_RX_INT | SCI_TX_INT);
	// sciEnableNotification(scilinREG, SCI_RX_INT | SCI_TX_INT);
}

void serialport_hal_enable_tx_isr(serialport_desc port_descriptor)
{
	switch(port_descriptor)
	{
		case PORT1:
			sciREG->SETINT = (uint32)SCI_TX_INT;
			break;
		case PORT2:
			scilinREG->SETINT = (uint32)SCI_TX_INT;
			break;
		case TM4C_PORT1:
			break;
		case TM4C_PORT2:
			break;
		case TM4C_PORT3:
			break;
		default:
			break;
	}
}

void serialport_hal_disable_tx_isr(serialport_desc port_descriptor)
{
	switch(port_descriptor)
	{
		case PORT1:
			sciREG->CLEARINT = (uint32)SCI_TX_INT;
			break;
		case PORT2:
			scilinREG->CLEARINT = (uint32)SCI_TX_INT;
			break;
		case TM4C_PORT1:
			break;
		case TM4C_PORT2:
			break;
		case TM4C_PORT3:
			break;
		default:
			break;
	}
}

int serialport_send_byte(serialport_desc port_descriptor, uint8_t byte_to_send)
{
	switch(port_descriptor)
	{
		case PORT1:
			sciSendByte(sciREG, byte_to_send);
			return 0;
		case PORT2:
			sciSendByte(scilinREG, byte_to_send);
			return 0;
		case TM4C_PORT1:
			canTransmit(canREG3, canMESSAGE_BOX4, &byte_to_send);
			break;
		case TM4C_PORT2:
			canTransmit(canREG3, canMESSAGE_BOX5, &byte_to_send);
			break;
		case TM4C_PORT3:
			canTransmit(canREG3, canMESSAGE_BOX6, &byte_to_send);
			break;
		default:
			return -1;
	}
}

uint8_t serialport_receive_byte(serialport_desc port_descriptor)
{
	uint8_t can_data = 0U;
	switch(port_descriptor)
	{
		case PORT1:
			return (uint8_t)sciReceiveByte(sciREG);
		case PORT2:
			return (uint8_t)sciReceiveByte(scilinREG);
		case TM4C_PORT1:
			canGetData(canREG3, canMESSAGE_BOX1, &can_data);
			return can_data;
			break;
		case TM4C_PORT2:
			canGetData(canREG3, canMESSAGE_BOX2, &can_data);
			return can_data;
			break;
		case TM4C_PORT3:
			canGetData(canREG3, canMESSAGE_BOX3, &can_data);
			return can_data;
		default:
			return 0;
	}
}