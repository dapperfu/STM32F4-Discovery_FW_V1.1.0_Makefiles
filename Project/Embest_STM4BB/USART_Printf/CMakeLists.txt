# USART_Printf project
add_stm32_project(USART_Printf
    HEAP_SIZE 8192
    STACK_SIZE 2048
    SOURCES
        src/main.c
        src/stm32f4xx_it.c
        src/system_stm32f4xx.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
        ${DISCOVERY}/stm32f4_discovery.c
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    INCLUDES
        inc
)

