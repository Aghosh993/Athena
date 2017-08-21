#include "hal_common_includes.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
  while(1);
}

void SVC_Handler(void)
{

}

void PendSV_Handler(void)
{
  
}