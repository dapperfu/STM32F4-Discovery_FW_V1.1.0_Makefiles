################################################################################
#
#	Flags
#		Linker, compiler, assembler flags for STM32F4 Discovery..
#
################################################################################

#
# Define FPU settings here
#
ifeq ($(USE_HARD_FPU), 0)
# Specifying ‘soft’ causes GCC to generate output containing library calls for floating-point operations
FPU+= -mfloat-abi=soft
else
# ‘Hard’ allows generation of floating-point instructions and uses FPU-specific calling conventions.
FPU+=-mfloat-abi=hard 
# Specifies what floating-point hardware (or hardware emulation) is available on the target. 
FPU+=-mfpu=fpv4-sp-d16
# __FPU_USED sets registry to enable FPU.
FPU+=-D__FPU_USED=1
endif

#
# Add prefixe to defines
#
INCDIR  = $(patsubst %,-I%,$(sort $(DINCDIR) $(UINCDIR)))
LIBDIR  = $(patsubst %,-L%,$(sort $(DLIBDIR) $(ULIBDIR)))

#
# Add -D prefix to defines.
#
CDEFS=$(patsubst %,-D%,$(sort $(DCDEFS) $(UCDEFS)))
ADEFS=$(patsubst %,-D%,$(sort $(DADEFS) $(UADEFS)))

#
# Combine Libraries. 
#
LIBS   +=$(DLIBS)
LIBS   +=$(ULIBS)

#
# MCU Flags
#
MCUFLAGS+=-mthumb
MCUFLAGS+=-mcpu=$(MCU)
MCUFLAGS+=$(FPU)

#
# Assembly Flags
#
ASFLAGS+=$(MCUFLAGS) 
ASFLAGS+=$(OPT)
ASFLAGS+=$(ADEFS)
ASFLAGS+=-Wa,-amhls=$(<:.s=.lst)

#
# C Flags
#
CPFLAGS+=$(MCUFLAGS)
CPFLAGS+=$(OPT)
CPFLAGS+=$(CDEFS)
CPFLAGS+=-Wall
CPFLAGS+=-Wstrict-prototypes
CPFLAGS+=-ffunction-sections
CPFLAGS+=-fdata-sections
CPFLAGS+=-Wa,-ahlms=$(<:.c=.lst)
CPFLAGS+=-MD
CPFLAGS+=-MP
CPFLAGS+=-MF
CPFLAGS+=.dep/$(@F).d

#
# Liner Flags
#
LDFLAGS+=$(MCUFLAGS)
LDFLAGS+=-nostartfiles
LDFLAGS+=-T$(LDSCRIPT)
LDFLAGS+=-Wl,-Map=$(PROJECT).map,--cref,--gc-sections,--no-warn-mismatch
LDFLAGS+=$(LIBDIR)