PROJECT=Example07

## Folder Paths.
# Relative path to STM32F4-Discovery-FW root.
STMFIRM=../../../..
# Discovery board path
DISCOVERY=$(STMFIRM)/Utilities/STM32F4-Discovery
# CMSIS Path
CMSIS=$(STMFIRM)/Libraries/CMSIS
# FreeRTOS 7.3.0
FREERTOS=$(STMFIRM)/FreeRTOS/FreeRTOS/Source
# Common Files for FreeRTOS Examples.
COMMON = ../Common

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes
# Defines
MCU     = cortex-m4
DEVICE  = STM32F40_41xxx
DEFS    = -DUSE_STDPERIPH_DRIVER -D$(DEVICE) -DUSE_USB_OTG_FS -DHSE_VALUE=8000000
MCFLAGS = -mcpu=$(MCU) -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork

# Compile Flags
OPTIMIZE  = -Os
CFLAGS    = $(MCFLAGS) $(CWARN) -MD -MP -MF .dep/$(@F).d
ASMFLAGS  = $(MCFLAGS)
LINKFLAG  = -Wl,-T,$(LINKER)

include $(COMMON)/Targets.mk