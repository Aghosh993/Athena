target remote localhost:3333
monitor reset halt
load tm4c_launchpad_basic_app.elf
monitor reset init
set confirm off
quit
