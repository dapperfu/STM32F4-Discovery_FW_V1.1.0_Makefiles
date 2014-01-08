################################################################################
#
# Common 
#	This is the 'global' include file. Only include this file and all others will
#	Automatically be included.
#
################################################################################
# Derive the project name from the current folder.
ifeq ($(PROJECT),)
PROJECT        = $(notdir $(CURDIR))
endif
# Set up stack and heap sizes & FPU Usage.
USE_HARD_FPU   = 1
HEAP_SIZE      = 8192
STACK_SIZE     = 1024
MCU  		   = cortex-m4
################################################################################
# Start of default section.
# List all default C defines here, like _DEBUG=1. -D is automatically added.
DCDEFS+=STM32F40_41xxx
DCDEFS+=USE_STDPERIPH_DRIVER
DCDEFS+=__HEAP_SIZE=$(HEAP_SIZE)
DCDEFS+=__STACK_SIZE=$(STACK_SIZE)
# List all default ASM defines here, like _DEBUG=1 -D is automatically added.
DADEFS+= 
# List all default directories to look for include files here
DINCDIR+= $(CMSIS)/Include
DINCDIR+= $(CMSIS)/Device/ST/STM32F4xx/Include
DINCDIR+= $(STMFIRM)/Utilities/STM32F4-Discovery
DINCDIR+= $(STM32F4xx_StdPeriph_Driver)/inc/
# List the default directory to look for the libraries here
DLIBDIR =
# List all default libraries here
DLIBS = 
# End of default section
################################################################################
# Include Complier Setup
include $(STMFIRM)/Project/Makefiles/Compiler.mk
# Include Compiler Flags
include $(STMFIRM)/Project/Makefiles/Flags.mk
# Include Flashing Program.
include $(STMFIRM)/Project/Makefiles/Flash.mk
# Include Set Paths
include $(STMFIRM)/Project/Makefiles/Paths.mk
# Include Sources
include $(STMFIRM)/Project/Makefiles/Sources.mk
# Include make targets.
include $(STMFIRM)/Project/Makefiles/Targets.mk