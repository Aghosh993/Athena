/*
  This is the main user software application
  In this case, we have below the code necessary to use the FreeRTOS
  kernel to toggle a set of LEDs on a STM32 F0 Discovery board.

  (c) Abhimanyu Ghosh, 2017
 */

#include "cpu_hal_interface.h"
#include "board_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

xQueueHandle pbq;

void SysTick_Handler(void) {
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        xPortSysTickHandler();
    }
    HAL_IncTick();
}

void myTask0(void *pvParameters)
{
  while(1)
  {
    board_led_on(LED1);
    vTaskDelay(1500/portTICK_RATE_MS);
    board_led_off(LED1);
    vTaskDelay(500/portTICK_RATE_MS);
  }
}

void myTask1(void *pvParameters)
{
  while(1)
  {
    board_led_on(LED2);
    vTaskDelay(250/portTICK_RATE_MS);
    board_led_off(LED2);
    vTaskDelay(250/portTICK_RATE_MS);
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

  int i = 0;

  pbq = xQueueCreate(1, sizeof(int));
  
  if (pbq == 0) {
    board_led_on(LED1);
    while(1); /* fatal error */
  }

  xTaskCreate(
      myTask0,                 /* Function pointer */
      "Task0",                          /* Task name - for debugging only*/
      configMINIMAL_STACK_SIZE,         /* Stack depth in words */
      (void*) NULL,                     /* Pointer to tasks arguments (parameter) */
      tskIDLE_PRIORITY + 2UL,           /* Task priority*/
      NULL                              /* Task handle */
  );

  xTaskCreate(
      myTask1,                 /* Function pointer */
      "Task1",                          /* Task name - for debugging only*/
      configMINIMAL_STACK_SIZE,         /* Stack depth in words */
      (void*) NULL,                     /* Pointer to tasks arguments (parameter) */
      tskIDLE_PRIORITY + 2UL,           /* Task priority*/
      NULL                              /* Task handle */
  );
  
  vTaskStartScheduler();

  /*
    Do nothing here... the FreeRTOS kernel should be running and executing all scheduled tasks...
   */
  while(1);

  return 0;
}
