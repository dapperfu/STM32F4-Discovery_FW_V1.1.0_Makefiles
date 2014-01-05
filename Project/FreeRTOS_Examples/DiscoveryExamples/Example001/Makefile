PROJECT=Example01
USE_HARD_FPU   = 1
HEAP_SIZE      = 8192
STACK_SIZE     = 2048
# Define optimisation level here
OPT 		   = 0 
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
#
# Define FPU settings here
#
ifeq ($(USE_HARD_FPU), 0)
FPU = -mfloat-abi=soft
else
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__FPU_USED=1
endif
# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes
# Defines
MCU     = cortex-m4
DEVICE  = STM32F40_41xxx
DEFS    = -DUSE_STDPERIPH_DRIVER -D$(DEVICE)
ADEFS   = -D__HEAP_SIZE=$(HEAP_SIZE) -D__STACK_SIZE=$(STACK_SIZE)

OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
MCFLAGS = -mthumb -mcpu=$(MCU) $(FPU)

# Compile Flags
OPTIMIZE  = -Os
CFLAGS    = $(MCFLAGS) $(CWARN) -MD -MP -MF .dep/$(@F).d -ffunction-sections -fdata-sections
ASMFLAGS  = $(MCFLAGS)
LDFLAGS    = $(MCFLAGS) -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(PROJECT).map,--cref,--gc-sections,--no-warn-mismatch

include $(COMMON)/Targets.mk