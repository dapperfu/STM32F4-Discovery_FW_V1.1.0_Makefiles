PROJECT=TIM_ComplementarySignals

BUILDDIR=.
TARGET=$(PROJECT).hex
EXECUTABLE=$(PROJECT).elf

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld 
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

# Used in Windows to handle absolute paths and use sh instead cmd.com
SHELL=/bin/sh
# Relative path to STM32F4-Discovery-FW root.
STMFIRM=../../..
# Include Directories.
STM32_INCLUDES = $(STMFIRM)/Utilities/STM32F4-Discovery/ \
	$(STMFIRM)/Libraries/CMSIS/Device/ST/STM32F4xx/Include/ \
	$(STMFIRM)/Libraries/CMSIS/Include/ \
	$(STMFIRM)/Libraries/CMSIS/Lib/ARM \
	$(STMFIRM)/Libraries/CMSIS/Lib/GCC \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/inc/ \
	$(STMFIRM)/Libraries/STM32_USB_Device_Library/Class/hid/inc \
	$(STMFIRM)/Libraries/STM32_USB_Device_Library/Core/inc/ \
	$(STMFIRM)/Libraries/STM32_USB_OTG_Driver/inc/ \
# Source Files
SRC = main.c \
	stm32f4xx_it.c \
	system_stm32f4xx.c \
	$(STMFIRM)/Utilities/STM32F4-Discovery/stm32f4_discovery.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
	$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
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
COBJS    = $(notdir $(SRC:.c=.o))
ASMOBJS  = $(notdir $(SRC:.s=.o))

# Compile Flags
OPTIMIZE  = -Os
CFLAGS    = $(MCFLAGS) -Wl,-T,$(LINKER)

# Targets
all: $(TARGET)

$(TARGET): $(EXECUTABLE)
	@echo Creating $@
	@$(CP) -O ihex $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	@echo Compiling $@
	@$(CC) $(DEFS) $(CFLAGS) $(OPTIMIZE) -I. -I./ $(IINCDIR) $^ -o $@
	
flash: all
	@echo Flashing $(TARGET)
	@C:\PROGRA~2\STMICR~1\STM32S~1\ST-LIN~1\ST-LIN~1.EXE -V -c SWD UR -P $(TARGET) -Rst

clean:
	@echo Removing $(EXECUTABLE) $(TARGET)
	@rm -rf $(EXECUTABLE) $(TARGET)