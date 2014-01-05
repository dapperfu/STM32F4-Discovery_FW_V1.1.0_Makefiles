# Target filenames
TARGET_HEX=$(PROJECT).hex
TARGET_BIN=$(PROJECT).bin
EXECUTABLE=$(PROJECT).elf

# Toolchain Prefix
TOOLCHAIN=arm-none-eabi-

CC=$(TOOLCHAIN)gcc
LD=$(TOOLCHAIN)ld 
AR=$(TOOLCHAIN)ar
AS=$(TOOLCHAIN)gcc -x assembler-with-cpp
CP=$(TOOLCHAIN)objcopy
OD=$(TOOLCHAIN)objdump

# Standard Peripheral Driver Path
STM32F4xx_StdPeriph_Driver=$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver

# Used in Windows to handle absolute paths and use sh instead cmd.com
SHELL=/bin/sh

# Makefile include with all peripheral driver files
include $(STM32F4xx_StdPeriph_Driver)/STM32F4xx_StdPeriph_Driver.mk
# Include Directories.
STM32_INCLUDES = .
STM32_INCLUDES+= $(STM32F4xx_INC)
STM32_INCLUDES+= $(CMSIS)/Device/ST/STM32F4xx/Include
STM32_INCLUDES+= $(CMSIS)/Include
STM32_INCLUDES+= $(FREERTOS)/include
STM32_INCLUDES+= $(FREERTOS)/portable/GCC/ARM_CM4F
STM32_INCLUDES+= $(CMSIS)/Lib/ARM 
STM32_INCLUDES+= $(CMSIS)/Lib/GCC
STM32_INCLUDES+= $(DISCOVERY)
STM32_INCLUDES+= $(COMMON)

# Source Files
SRC = main.c
SRC+= $(COMMON)/basic_io.c
SRC+= $(COMMON)/uart_support.c
SRC+= $(COMMON)/utils.c
SRC+= $(COMMON)/debug.c
SRC+= $(FREERTOS)/croutine.c
SRC+= $(FREERTOS)/list.c
SRC+= $(FREERTOS)/queue.c
SRC+= $(FREERTOS)/tasks.c
SRC+= $(FREERTOS)/timers.c
SRC+= $(FREERTOS)/portable/MemMang/heap_1.c
SRC+= $(FREERTOS)/portable/GCC/ARM_CM4F/port.c
SRC+= $(DISCOVERY)/stm32f4_discovery.c
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
SRC+= $(STM32F4xx_SRC)

# Object files groups
COBJS    = $(SRC:.c=.o)
ASMOBJS  = $(STARTUP:.s=.o)

# Startup assembly files
STARTUP = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/startup_stm32f4xx.s
# Linker File
LDSCRIPT = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/stm32f4xxxg_flash.ld

# Convert Include Directory to -I{dir} format
IINCDIR = $(patsubst %,-I%,$(STM32_INCLUDES))

# Targets
.PHONY: all
all: $(TARGET_HEX) $(TARGET_BIN)

$(TARGET_HEX): $(EXECUTABLE)
	@echo Creating $@
	@$(CP) -O ihex $^ $@
	
$(TARGET_BIN): $(EXECUTABLE)
	@echo Creating $@
	@$(CP) -O binary $^ $@

$(EXECUTABLE): $(COBJS) $(ASMOBJS)
	@echo Linking $@
	@$(CC) $(CWARN) $(DEFS) $(CFLAGS) $(LINKFLAG) $(OPTIMIZE) $(IINCDIR) $(COBJS) $(ASMOBJS) -o $@

$(COBJS): %.o : %.c
	@echo Compiling $(notdir $<)
	@$(CC) -c $(CWARN) $(DEFS) $(CFLAGS) $(IINCDIR) $< -o $@
	
$(ASMOBJS): %.o : %.s
	@echo Compiling $(notdir $<)
	@$(AS) -c $(ASMFLAGS) $(IINCDIR) $< -o $@

test: $(COBJS) $(ASMOBJS)
	@echo $(@F)
	
.PHONY: flash
.SINGLESHELL: flash
flash: all
	@echo Flashing $(TARGET)
	@C:\PROGRA~2\STMICR~1\STM32S~1\ST-LIN~1\ST-LIN~1.EXE -V -c SWD UR -P $(TARGET_HEX) -Rst

.PHONY: clean
clean:
	@echo Removing $(TARGET_HEX) $(TARGET_BIN)
	@rm -rf .dep/ $(TARGET_HEX) $(TARGET_BIN) $(COBJS) $(ASMOBJS)

#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***