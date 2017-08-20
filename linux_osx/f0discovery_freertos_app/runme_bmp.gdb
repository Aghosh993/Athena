target extended-remote /dev/ttyACM0
monitor swdp_scan
attach 1
load f0discovery_freertos_app.elf
kill