# STM32F4xx_FPU_FFT_Example project
add_stm32_project(STM32F4xx_FPU_FFT_Example
    HEAP_SIZE 8192
    STACK_SIZE 2048
    OPTIMIZATION -O3
    SOURCES
        src/main.c
        src/stm32f4xx_it.c
        src/system_stm32f4xx.c
        src/arm_fft_bin_data.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
        ${DISCOVERY}/stm32f4_discovery.c
        ${COMMON_STM32F4xx_SOURCES}
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    INCLUDES
        inc
        ${CMSIS}/Device/ARM/ARMCM4/Include
    DEFINES
        ARM_MATH_CM4
    LIBRARIES
        arm_cortexM4lf_math
    LIBRARY_DIRS
        ${CMSIS}/Lib/GCC
)

# Add -fsingle-precision-constant flag for this project
target_compile_options(STM32F4xx_FPU_FFT_Example.elf PRIVATE
    -fsingle-precision-constant
)

