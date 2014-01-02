PROJECT=IO_Toggle

BUILDDIR=.
TARGET_HEX=$(PROJECT).hex
TARGET_BIN=$(PROJECT).bin
EXECUTABLE=$(PROJECT).elf

TOOLCHAIN=arm-none-eabi-

CC=$(TOOLCHAIN)gcc
LD=$(TOOLCHAIN)ld 
AR=$(TOOLCHAIN)ar
AS=$(TOOLCHAIN)as
CP=$(TOOLCHAIN)objcopy
OD=$(TOOLCHAIN)objdump

# Used in Windows to handle absolute paths and use sh instead cmd.com
SHELL=/bin/sh

## Folder Paths.
# Relative path to STM32F4-Discovery-FW root.
STMFIRM=../../..
# Discovery board path
DISCOVERY=$(STMFIRM)/Utilities/STM32F4-Discovery

# Libraries
# CMSIS Path
CMSIS=$(STMFIRM)/Libraries/CMSIS
# STM32 USB Device Library
STM32_USB_Device_Library=$(STMFIRM)/Libraries/STM32_USB_Device_Library
# STM32 USB HOST Library
STM32_USB_HOST_Library=$(STMFIRM)/Libraries/STM32_USB_HOST_Library
# STM32 USB OTG Driver
STM32_USB_OTG_Driver=$(STMFIRM)/Libraries/STM32_USB_OTG_Driver
# Standard Peripheral Driver Path
STM32F4xx_StdPeriph_Driver=$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver

# Makefile include with all peripheral driver files
include $(STM32F4xx_StdPeriph_Driver)/STM32F4xx_StdPeriph_Driver.mk
include $(STM32_USB_OTG_Driver)/STM32_USB_OTG_Driver.mk
# Include Directories.
STM32_INCLUDES = .
STM32_INCLUDES+= $(STM32F4xx_INC)
STM32_INCLUDES+= $(STMFIRM)/Utilities/STM32F4-Discovery
STM32_INCLUDES+= $(CMSIS)/Device/ST/STM32F4xx/Include
STM32_INCLUDES+= $(CMSIS)/Include
STM32_INCLUDES+= $(CMSIS)/Lib/ARM 
STM32_INCLUDES+= $(CMSIS)/Lib/GCC
STM32_INCLUDES+= $(STMFIRM)/Libraries/STM32_USB_Device_Library/Class/hid/inc
STM32_INCLUDES+= $(STMFIRM)/Libraries/STM32_USB_Device_Library/Core/inc
STM32_INCLUDES+= $(STM32_USB_OTG_INC)

# Source Files
SRC = main.c \
	stm32f4xx_it.c \
	system_stm32f4xx.c \
	$(DISCOVERY)/stm32f4_discovery.c \
	$(STM32F4xx_SRC)
	
# Startup assembly files
STARTUP = $(STMFIRM)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s
# Linker File
LINKER  = ./TrueSTUDIO/$(PROJECT)/stm32_flash.ld

# Convert Include Directory to -I{dir} format
IINCDIR   = $(patsubst %,-I%,$(STM32_INCLUDES))
# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes
# Defines
MCU     = cortex-m4
DEVICE  = STM32F40_41xxx
DEFS    = -DUSE_STDPERIPH_DRIVER -D$(DEVICE) -DUSE_USB_OTG_FS -DHSE_VALUE=8000000
MCFLAGS = -mcpu=$(MCU) -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork
# Object files groups
COBJS    = $(SRC:.c=.o)
ASMOBJS  = $(STARTUP:.s=.o)

# Compile Flags
OPTIMIZE  = -O3
CFLAGS    = $(MCFLAGS)
LINKFLAG  = -Wl,-T,$(LINKER)

# Clean 
CLEAN=$(EXECUTABLE) $(TARGET) obj/

#$(addprefix ./obj/,$(notdir $(COBJS))) $(addprefix ./obj/,$(notdir $(ASMOBJ)))
	
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
	@$(CC) $(CWARN) $(DEFS) $(CFLAGS) $(LINKFLAG) $(OPTIMIZE) $(IINCDIR) $(addprefix obj/,$(notdir $(COBJS) $(ASMOBJS))) -o $@

$(COBJS): %.o : %.c
	@echo Compiling $(notdir $<) obj/$(notdir $@)
	@$(CC) -c $(CWARN) $(DEFS) $(CFLAGS) $(IINCDIR) $< -o obj/$(notdir $@)
	
$(ASMOBJS): %.o : %.s
	@echo Compiling $(notdir $<) obj/$(notdir $@)
	@$(AS) -c $(CFLAGS) $(IINCDIR) $< -o obj/$(notdir $@)

obj/: 
	mkdir -p obj/
	
.PHONY: flash
flash: all
	@echo Flashing $(TARGET)
	@C:\PROGRA~2\STMICR~1\STM32S~1\ST-LIN~1\ST-LIN~1.EXE -V -c SWD UR -P $(TARGET) -Rst

.PHONY: clean
clean:
	@echo Removing $(CLEAN)
	rm -rf $(CLEAN)
	
.PHONY: force
force: clean $(TARGET) 