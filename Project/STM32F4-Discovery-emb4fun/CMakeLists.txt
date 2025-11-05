# STM32F4-Discovery-emb4fun project
add_stm32_project(test
    HEAP_SIZE 8192
    STACK_SIZE 2048
    SOURCES
        src/main.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${COMMON_CMSIS_SOURCES}
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    DEFINES
        RUN_FROM_FLASH=1
)

