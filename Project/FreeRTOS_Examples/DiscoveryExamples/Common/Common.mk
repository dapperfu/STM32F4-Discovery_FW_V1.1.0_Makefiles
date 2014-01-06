# Derive the project name from the current folder.
PROJECT        = $(notdir $(CURDIR))

# Set up stack and heap sizes & FPU Usage.
USE_HARD_FPU   = 1
HEAP_SIZE      = 8192
STACK_SIZE     = 2048
MCU  		   = cortex-m4

# Compiler programs.
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp

# Flashing Program & Flags
FLASH      = C:\PROGRA~2\STMICR~1\STM32S~1\ST-LIN~1\ST-LIN~1.EXE
FLASHFLAGS = -V -c SWD UR -P $(PROJECT).hex -Rst

# List all default C defines here, like -D_DEBUG=1
DDEFS = -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List all default directories to look for include files here
DINCDIR = 

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 
# End of default section
##############################################################################################

## Folder Paths.
# Relative path to STM32F4-Discovery-FW root.
STMFIRM=../../../..
## Utilities
# Discovery board path
DISCOVERY=$(STMFIRM)/Utilities/STM32F4-Discovery
## Libraries
# CMSIS Path
CMSIS=$(STMFIRM)/Libraries/CMSIS
# Standard Peripheral Driver Path
STM32F4xx_StdPeriph_Driver=$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver
# FreeRTOS 7.3.0
FREERTOS=$(STMFIRM)/FreeRTOS/FreeRTOS/Source
# Common Files for FreeRTOS Examples.
COMMON = ../Common

# Makefile include with all peripheral driver files
include $(STM32F4xx_StdPeriph_Driver)/STM32F4xx_StdPeriph_Driver.mk

#
# Define linker script file here
#
LDSCRIPT = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/stm32f4xxxg_flash.ld

#
# Define FPU settings here
#
ifeq ($(USE_HARD_FPU), 0)
FPU = -mfloat-abi=soft
else
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__FPU_USED=1
endif

# Define ASM defines here
UADEFS = 

# List C source files here
SRC+= main.c
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
SRC+= $(DISCOVERY)/stm32f4_discovery.c
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
SRC+= $(STM32F4xx_SRC)

# List ASM source files here
ASRC = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/startup_stm32f4xx.s

# List all user directories here
UINCDIR+= $(COMMON)
UINCDIR+= $(CMSIS)/Include
UINCDIR+= $(CMSIS)/Device/ST/STM32F4xx/Include
UINCDIR+= $(DISCOVERY)
UINCDIR+= $(STMFIRM)/Utilities/STM32F4-Discovery
UINCDIR+= $(FREERTOS)/include
UINCDIR+= $(FREERTOS)/portable/GCC/ARM_CM4F
UINCDIR+= $(STM32F4xx_INC)

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = 

# Define optimisation level here
OPT = -O0 

#
# End of user defines
##############################################################################################

INCDIR  = $(patsubst %,-I%,$(sort $(DINCDIR) $(UINCDIR)))
LIBDIR  = $(patsubst %,-L%,$(sort $(DLIBDIR) $(ULIBDIR)))

ADEFS   = $(DADEFS) $(UADEFS) -D__HEAP_SIZE=$(HEAP_SIZE) -D__STACK_SIZE=$(STACK_SIZE)
OBJS    = $(SRC:.c=.o) $(ASRC:.s=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mthumb -mcpu=$(MCU) $(FPU)

ASFLAGS  = $(MCFLAGS) $(OPT) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)

CPFLAGS  = $(MCFLAGS) $(OPT) -gdwarf-2 -Wall -Wstrict-prototypes -fverbose-asm 
CPFLAGS += -ffunction-sections -fdata-sections -Wa,-ahlms=$(<:.c=.lst) $(DDEFS)

LDFLAGS  = $(MCFLAGS) -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(PROJECT).map,--cref,--gc-sections,--no-warn-mismatch $(LIBDIR)

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(PROJECT).elf $(PROJECT).hex


%.o : %.c
	@echo Compiling $<
	@$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%.o : %.s
	@echo Compiling $<
	@$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	@echo Linking $@
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@
  
%hex: %elf
	@$(CP) -O ihex $< $@
	
.PHONY: flash
.SINGLESHELL: flash
flash: $(PROJECT).hex
	@echo Flashing $(TARGET)
	@$(FLASH) $(FLASHFLAGS)

clean:
	-rm -f $(OBJS)
	-rm -f $(PROJECT).elf
	-rm -f $(PROJECT).map
	-rm -f $(PROJECT).hex
	-rm -f $(SRC:.c=.c.bak)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.s.bak)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***