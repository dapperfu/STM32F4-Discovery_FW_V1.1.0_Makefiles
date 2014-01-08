## Source Files
#
# Linker Scripts.
#
LDSCRIPT = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/stm32f4xxxg_flash.ld
#
# ASM source files here
#
ASRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/startup_stm32f4xx.s
#
# C source files here
#
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
SRC+= $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
SRC+= $(DISCOVERY)/stm32f4_discovery.c
# List of all the board related files.
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/misc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_adc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_can.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_crc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_cryp.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_cryp_aes.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_cryp_des.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_cryp_tdes.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_dac.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_dbgmcu.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_dcmi.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_dma.c
#SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_dma2d.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_exti.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_flash.c
#SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_fmc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_fsmc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_gpio.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_hash.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_hash_md5.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_hash_sha1.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_i2c.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_iwdg.c
#SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_ltdc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_pwr.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_rcc.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_rng.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_rtc.c
#SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_sai.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_sdio.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_spi.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_syscfg.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_tim.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_usart.c
SRC+=$(STM32F4xx_StdPeriph_Driver)/src/stm32f4xx_wwdg.c
