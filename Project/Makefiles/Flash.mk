################################################################################
#
# Paths
#	Paths for STM32F4 Discovery
#
################################################################################
## Flashing Program & Flags
ifeq ($(OS),Windows_NT)
FLASH      = C:\PROGRA~2\STMICR~1\STM32S~1\ST-LIN~1\ST-LIN~1.EXE
FLASHFLAGS+= -V -c SWD UR -P $(PROJECT).hex 0x08000000 -V -Rst
else ifeq ($(shell uname), Linux)
FLASH      = stlink
FLASHFLAGS+= 
else
FLASH      = stlink
FLASHFLAGS+= 
endif