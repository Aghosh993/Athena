#!/bin/bash
openocd -f board/ek-tm4c123gxl.cfg &
$1/arm-none-eabi-gdb -x runme_icdi.gdb
pkill openocd