#!/bin/bash
$1/JLinkGDBServer &
$2/arm-none-eabi-gdb -x runme.gdb
pkill JLinkGDBServer