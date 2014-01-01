# STM32F4xx StdPeriph Driver Path
$(STMDRIVER)=$(STMFIRM)/Libraries/STM32F4xx_StdPeriph_Driver/
# Required include directories
DRIVERINC+= ${STMDRIVER}/src/inc/
# List of all the board related files.
DRIVERSRC+=${STMDRIVER}/src/misc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_adc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_can.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_crc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_cryp.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_cryp_aes.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_cryp_des.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_cryp_tdes.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_dac.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_dbgmcu.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_dcmi.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_dma.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_exti.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_flash.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_fsmc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_gpio.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_hash.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_hash_md5.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_hash_sha1.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_i2c.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_iwdg.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_pwr.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_rcc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_rng.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_rtc.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_sdio.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_spi.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_syscfg.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_tim.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_usart.c
DRIVERSRC+=${STMDRIVER}/src/stm32f4xx_wwdg.c
