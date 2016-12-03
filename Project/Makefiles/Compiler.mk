################################################################################
#
#	Compiler settings for STM32F4 Discovery
#
################################################################################
## Compiler programs.
TRGT = arm-none-eabi-
# Program names.
CC= $(TRGT)gcc
CP= $(TRGT)objcopy
AS= $(TRGT)gcc -x assembler-with-cpp
