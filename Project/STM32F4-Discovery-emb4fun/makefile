#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!    
#
##############################################################################################
# 
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#

##############################################################################################
# Start of default section
#

TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
BIN  = $(CP) -O ihex 

MCU  = cortex-m4

# List all default C defines here, like -D_DEBUG=1
DDEFS =

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List all default directories to look for include files here
DINCDIR = 

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

# 
# Define project name and Ram/Flash mode here
PROJECT        = test
RUN_FROM_FLASH = 0
USE_HARD_FPU   = 1
HEAP_SIZE      = 8192
STACK_SIZE     = 2048

#
# Define linker script file here
#
ifeq ($(RUN_FROM_FLASH), 0)
LDSCRIPT = ./prj/stm32f4xx_ram.ld
FULL_PRJ = $(PROJECT)_ram
else
LDSCRIPT = ./prj/stm32f4xxxg_flash.ld
FULL_PRJ = $(PROJECT)_rom
endif

#
# Define FPU settings here
#
ifeq ($(USE_HARD_FPU), 0)
FPU =
else
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__FPU_USED=1
endif


# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

# List C source files here
SRC  = ./cmsis/device/system_stm32f4xx.c \
       ./src/syscalls.c \
       ./src/main.c

# List ASM source files here
ASRC = ./cmsis/device/startup_stm32f4xx.s

# List all user directories here
UINCDIR = ./inc \
          ./cmsis/core \
          ./cmsis/device

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = 

# Define optimisation level here
OPT = -O0 
#OPT = -O2 -falign-functions=16 -fno-inline -fomit-frame-pointer

#
# End of user defines
##############################################################################################


INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

ifeq ($(RUN_FROM_FLASH), 0)
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=0 -DVECT_TAB_SRAM
else
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=1
endif

ADEFS   = $(DADEFS) $(UADEFS) -D__HEAP_SIZE=$(HEAP_SIZE) -D__STACK_SIZE=$(STACK_SIZE)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mthumb -mcpu=$(MCU) $(FPU)

ASFLAGS  = $(MCFLAGS) $(OPT) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)

CPFLAGS  = $(MCFLAGS) $(OPT) -gdwarf-2 -Wall -Wstrict-prototypes -fverbose-asm 
CPFLAGS += -ffunction-sections -fdata-sections -Wa,-ahlms=$(<:.c=.lst) $(DEFS)

LDFLAGS  = $(MCFLAGS) -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--gc-sections,--no-warn-mismatch $(LIBDIR)

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(FULL_PRJ).elf $(FULL_PRJ).hex


%.o : %.c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%.o : %.s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@
  
%hex: %elf
	$(BIN) $< $@

clean:
	-rm -f $(OBJS)
	-rm -f $(FULL_PRJ).elf
	-rm -f $(FULL_PRJ).map
	-rm -f $(FULL_PRJ).hex
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