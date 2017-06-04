/*
	This is the main user software application
	In this case, we have below the code necessary to toggle a set of LEDs on an RM48L950-based autopilot PCB at 20 Hz.

	(c) Abhimanyu Ghosh, 2017
 */

#include "cpu_hal_interface.h"
#include "board_led.h"
#include "board_adc.h"
#include "serial_comms_highlevel.h"
#include "system_shell.h"

#include "foo.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

volatile serialport console_serial_port;

void shell_clear(int argc, char** argv)
{
  clear_buffer();
}

void ledcontrol(int argc, char** argv)
{
  led l = GIO1;

  if(argc < 2)
  {
    printf("Utility to set or clear a given GPIO line on the board\r\n");
    printf("Usage: set [GPIO] [on/off]\r\n");
    printf("[GPIO] can be:\r\n");
    printf("gio1, gio2, gio3, gio4, gp_led, gio6\r\n");
  }
  else
  {
    if(strncmp(argv[0], "gio1", 4) == 0)
    {
      l = GIO1;
    }
    else if(strncmp(argv[0], "gio2", 4) == 0)
    {
      l = GIO2;
    }
    else if(strncmp(argv[0], "gio3", 4) == 0)
    {
      l = GIO3;
    }
    else if(strncmp(argv[0], "gio4", 4) == 0)
    {
      l = GIO4;
    }
    else if(strncmp(argv[0], "gp_led", 6) == 0)
    {
      l = GP_LED;
    }
    else if(strncmp(argv[0], "gio6", 4) == 0)
    {
      l = GIO6;
    }
    else
    {
      printf("ERROR: Invalid GPIO line selection!!\r\n");
      return;
    }

    if(strncmp(argv[1], "on", 3) == 0)
    {
      board_led_on(l);
    }
    if(strncmp(argv[1], "off", 3) == 0)
    {
      board_led_off(l);
    }
  }
}

void analogtest(int argc, char** argv)
{
  char c;
  printf("Press 1 to see generic ADC channels, 2 to see Battery/Current Monitor channels or 3 to see Differential and Absolute pressure sensor raw voltage data\r\n");
  printf("Alternatively, press e to exit\r\n");
  
  while(1)
  {
    scanf("%c", &c);
    if(c == '1')
    {
      board_adc_update_blocking();
      printf("%f %f %f %f %f %f %f\r\n", board_adc_volts(AD1), board_adc_volts(AD2), board_adc_volts(AD3),
                                          board_adc_volts(AD4), board_adc_volts(AD5), board_adc_volts(AD6),
                                          board_adc_volts(AD7), board_adc_volts(AD8));
    }
    else if(c == '2')
    {
      board_adc_update_blocking();
      printf("VBAT1: %f, VBAT2: %f, Current (mA): %f\r\n", 8.5f*board_adc_volts(VBAT1), 8.5f*board_adc_volts(VBAT2), 1000.0f*board_adc_volts(INA_SENSE));
    }
    else if(c == '3')
    {
      board_adc_update_blocking();
      printf("Absolute: %f, Differential: %f\r\n", board_adc_volts(P_SENSOR_1), board_adc_volts(P_SENSOR_2));
    }
    else if(c == 'e')
    {
      printf("Exiting...\r\n");
      return;
    }
    else
    {
      printf("ERROR: Invalid option!!\r\n");
    }
  }
}

int main()
{
  /*
    Initialize the PLL, clock tree to all peripherals, flash and Systick 1 ms time reference:
   */
  cpu_init();
  /*
    Initialize the GPIO (General-Purpose I/O) subsystem pins that are connected to the LEDs on the board:
   */
  board_led_init();

  /*
    Initialize ADC:
   */
  board_adc_init();

  int i = 0;

  // Initialize the shell and underlying serial port API at 460800 baud, 8n1 on SCI1:
  setup_system_shell();

  if(install_cmd("clear", shell_clear) < 0)
  {
    printf("Install error in command clear\r\n");
  }

  if(install_cmd("set", ledcontrol) < 0)
  {
    printf("Install error in command set\r\n");
  }

  if(install_cmd("adc", analogtest) < 0)
  {
    printf("Install error in command adc\r\n");
  }

  printf("Initialized all drivers...\r\n");

  printf("Initialized system shell...\r\n now installing apps...\r\n");

  while(1)
  {
    shell_run(); // Keep prompting for more commands and processing appropriately...
  }
  return 0;
}
