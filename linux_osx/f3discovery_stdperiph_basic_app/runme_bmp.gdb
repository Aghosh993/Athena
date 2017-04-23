target extended-remote /dev/ttyACM0
monitor swdp_scan
attach 1
load f3discovery_stdperiph_basic_app.elf
kill