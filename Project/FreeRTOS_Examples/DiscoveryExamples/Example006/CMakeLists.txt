# Example006 FreeRTOS project
add_stm32_project(Example006
    SOURCES
        main.c
        ../Common/basic_io.c
        ../Common/utils.c
        ../Common/debug.c
        ${FREERTOS}/croutine.c
        ${FREERTOS}/list.c
        ${FREERTOS}/queue.c
        ${FREERTOS}/tasks.c
        ${FREERTOS}/timers.c
        ${FREERTOS}/portable/MemMang/heap_1.c
        ${FREERTOS}/portable/GCC/ARM_CM4F/port.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${COMMON_CMSIS_SOURCES}
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    INCLUDES
        ../Common
        ${FREERTOS}/include
        ${FREERTOS}/portable/GCC/ARM_CM4F
)

