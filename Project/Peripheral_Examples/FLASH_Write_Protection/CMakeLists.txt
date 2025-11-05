# FLASH_Write_Protection project
add_stm32_project(FLASH_Write_Protection
    SOURCES
        main.c
        stm32f4xx_it.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${COMMON_CMSIS_SOURCES}
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
)
