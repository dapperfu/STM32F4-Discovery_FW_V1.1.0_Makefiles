################################################################################
#
#	Compiler settings for STM32F4 Discovery
#
################################################################################
## Compiler programs.
ifeq ($(TRGT),)
ifeq ($(OS),Windows_NT)
TRGT = arm-none-eabi-
else ifeq ($(shell uname), Linux)
TRGT = /opt/gcc-arm-none-eabi/bin/arm-none-eabi-
else
TRGT = arm-none-eabi-
endif
endif
# Program names.
CC= $(TRGT)gcc
CP= $(TRGT)objcopy
AS= $(TRGT)gcc -x assembler-with-cpp