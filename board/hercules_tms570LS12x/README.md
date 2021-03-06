# TMS570 HAL (Hardware Abstraction Layer)

This directory contains the files generated by TI's HALcogen code generation tool to interface with the TMS570LS1224PGE Microcontroller from their Hercules line of processors. In this case, the HAL is generated in a manner specific to the chip's use in TI's XL2-TMS57012 Launchpad evaluation board.

# Enabled features

The following features are currently enabled:

- GIOB: Pins 1 and 2 set as outputs for the user LEDs on the board
- I2C: 400 kHz, for IMU/other interface
- SPI: 1 MHz, for high-speed bus interface to IMU and other peripherals
- RTI: Set to 1 kHz compare interrupt to serve as time base
- CAN1: 500 Kbps, with arbitration ID 1-4 for TX mailboxes and 5-8 for RX mailboxes. The RX mailboxes also have interrupt requests enabled.
- SCI1 and SCILIN in SCI mode: both set to 115200 baud, 8n1 with TX and RX interrupts enabled

# Notes on updating this directory structure

Note that the "notification.c" file is missing from the src/ sub-directory. This is because it is application-specific and therefore located in the user_source/hal_interface directory in the auto-generated project structure created by the mkproject.sh script. Also, sys_main.c is removed as the main application is located in the individual project directory. Finally, the "sys_link.ld" linker config file is moved to the project directory, and renamed "linker.ld"

If the code in this directory is to be uploaded, the include/ and source/ directories generated by HALcogen can simply be copied over and renamed, and the above changes made to preserve to structure of this repository.
