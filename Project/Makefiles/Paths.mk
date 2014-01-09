################################################################################
#
# Paths
#	Paths for STM32F4 Discovery
#
################################################################################
# Relative path to STM32F4-Discovery-FW root.
ifeq ($(STMFIRM),)
STMFIRM=../../..
endif
## Utilities
# Discovery board path
DISCOVERY=$(STMFIRM)/Utilities/STM32F4-Discovery
## Libraries
# CMSIS Path
CMSIS=$(STMFIRM)/Libraries/CMSIS
# Standard Peripheral Driver Path
STM32F4xx_StdPeriph_Driver=$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver
# FreeRTOS
FREERTOS=$(STMFIRM)/FreeRTOS/FreeRTOS/Source