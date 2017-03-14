target remote localhost:2331
monitor speed 1000
monitor flash device =  LM4F232H5QD
monitor halt
monitor reset
load tm4c_launchpad_basic_app.elf
set confirm off
quit
