# Relative path to STM32F4-Discovery-FW root.
STMFIRM=../../../..
# Common Files for FreeRTOS Examples.
COMMON = ../Common
# List C source files here
SRC+= main.c
SRC+= $(COMMON)/basic_io.c
SRC+= $(COMMON)/utils.c
SRC+= $(COMMON)/debug.c
SRC+= $(FREERTOS)/croutine.c
SRC+= $(FREERTOS)/list.c
SRC+= $(FREERTOS)/queue.c
SRC+= $(FREERTOS)/tasks.c
SRC+= $(FREERTOS)/timers.c
SRC+= $(FREERTOS)/portable/MemMang/heap_1.c
SRC+= $(FREERTOS)/portable/GCC/ARM_CM4F/port.c

# List all user directories here
UINCDIR+= $(COMMON)
UINCDIR+= $(FREERTOS)/include
UINCDIR+= $(FREERTOS)/portable/GCC/ARM_CM4F

# Common Makefile for all projects.
include $(STMFIRM)/Project/Makefiles/Common.mk