# Based on https://github.com/sergioprado/bare-metal-arm/blob/master/Makefile
# But heavily-edited for our purposes:
# (c) Abhimanyu Ghosh, 2016
ATHENA_PATH=athroot
TOOLCHAIN_ROOT=$(ATHENA_PATH)/arm-none-eabi-gcc_5_4_BE/gcc-arm-none-eabi-5_4-2017q1_BE_LINUX
TOOLCHAIN=$(TOOLCHAIN_ROOT)/bin/
JLINK_PATH=../../../JLink_Linux_V480_x86_64
PREFIX=$(TOOLCHAIN)/arm-none-eabi-

ARCHFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -I$(TOOLCHAIN_ROOT)/arm-none-eabi/include -fsingle-precision-constant 
CFLAGS=-nostdlib -ffunction-sections -I$(ATHENA_PATH)/arch/tivaware_tm4c/ -I$(ATHENA_PATH)/arch/tivaware_tm4c/inc/ -I$(ATHENA_PATH)/arch/tivaware_tm4c/driverlib/ -I./user_include -I./user_include/hal_interface -g -O2 -Wall -Dgcc -DTARGET_IS_TM4C123_RA3 -DPART_TM4C123GH6PM
LDFLAGS=-Wl,--gc-sections,-Map,$(TARGET).map,-Tlinker.ld --entry ResetISR
LDFLAGS+=$(ARCHFLAGS)

CC=$(PREFIX)gcc
LD=$(PREFIX)gcc
OBJCOPY=$(PREFIX)objcopy
SIZE=$(PREFIX)size
RM=rm -f

TARGET=tm4c_launchpad_basic_app

SRC=$(wildcard $(ATHENA_PATH)/arch/tivaware_tm4c/driverlib/*.c)
ASM_SRC=$(wildcard $(ATHENA_PATH)/arch/tivaware_tm4c/driverlib/*.s)
USER_SRC=$(wildcard user_source/*.c)
USER_SRC+=$(wildcard user_source/hal_interface/*.c)
USER_ASM_SRC=$(wildcard user_source/*.s)

OBJ=$(patsubst %.c, %.o, $(SRC))
ASM_OBJS=$(patsubst %.s, %.o, $(ASM_SRC))
TARGET_OBJ=$(TARGET).o
USER_OBJ=$(patsubst %.c, %.o, $(USER_SRC))
USER_ASM_OBJ=$(patsubst %.s, %.o, $(USER_ASM_SRC))

DEPS:=$(OBJ:.o=.d)
TARGET_DEPS:=$(TARGET_OBJ:.o=.d)
USER_DEPS:=$(USER_OBJ:.o=.d)

all: build size
build: elf srec bin 
elf: $(TARGET).elf
srec: $(TARGET).srec
bin: $(TARGET).bin
md5sums: all
	md5sum $(TARGET).elf > user_app_md5sum
check: all
	md5sum $(TARGET).elf > tmp && diff tmp user_app_md5sum && rm tmp

icdi: all
	./load_fw_icdi.sh $(TOOLCHAIN)

jtag: all
	./load_fw.sh $(JLINK_PATH) $(TOOLCHAIN)

clean:
	$(RM) $(TARGET_OBJ) $(TARGET).srec $(TARGET).elf $(TARGET).bin $(TARGET).map $(USER_ASM_OBJ) $(USER_OBJ) $(USER_DEPS) $(TARGET_DEPS)

hal_clean:
	$(RM) $(OBJ) $(ASM_OBJS) $(DEPS)

$(TARGET).elf: $(ASM_OBJS) $(USER_ASM_OBJ) $(OBJ) $(TARGET_OBJ) $(USER_OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ) $(ASM_OBJS) $(USER_ASM_OBJ) $(TARGET_OBJ) $(USER_OBJ) -lm -lc

%.o: %.s
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $@ $<

-include $(DEPS)
-include $(TARGET_DEPS)
-include $(USER_DEPS)

%.o: %.c
	$(CC) $(ARCHFLAGS) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(ARCHFLAGS) $(CFLAGS) -c -o $@ $<

%.srec: %.elf
	$(OBJCOPY) -O srec $< $@

%.bin: %.elf
	    $(OBJCOPY) -O binary $< $@

size: $(TARGET).elf
	$(SIZE) $(TARGET).elf

.PHONY: clean