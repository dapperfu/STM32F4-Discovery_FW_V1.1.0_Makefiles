################################################################################
#
# Common make file for STM32F4 Peripheral Examples
#
################################################################################
STMFIRM=../../..
SRC+= main.c
SRC+= stm32f4xx_it.c
include $(STMFIRM)/Project/Makefiles/Common.mk