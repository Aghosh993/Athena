#!/bin/bash
$1/JLinkGDBServer -Device RM48L9x &
$2/arm-none-eabi-gdb --batch --command=runme.gdb
pkill JLinkGDBServer