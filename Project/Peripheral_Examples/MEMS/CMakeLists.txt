# MEMS project
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
add_stm32_project(MEMS
    SOURCES
        main.c
        stm32f4xx_it.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${DISCOVERY}/stm32f4_discovery_lis302dl.c
        ${COMMON_CMSIS_SOURCES}
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
)

