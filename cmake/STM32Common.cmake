################################################################################
# STM32 Common CMake Configuration
# This file provides common functions and settings for STM32F4 projects
################################################################################

# Detect toolchain path
if(DEFINED ENV{ARM_TOOLCHAIN_PATH})
    set(ARM_TOOLCHAIN_PATH "$ENV{ARM_TOOLCHAIN_PATH}")
else()
    # Try common locations
    if(EXISTS "/opt/gcc-arm-none-eabi/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi")
        set(ARM_TOOLCHAIN_PATH "/opt/gcc-arm-none-eabi/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi")
    elseif(EXISTS "/usr/bin/arm-none-eabi-gcc")
        set(ARM_TOOLCHAIN_PATH "")
    else()
        message(FATAL_ERROR "ARM toolchain not found. Please set ARM_TOOLCHAIN_PATH environment variable or install toolchain.")
    endif()
endif()

# Set toolchain prefix
if(ARM_TOOLCHAIN_PATH)
    set(TOOLCHAIN_PREFIX "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-")
else()
    set(TOOLCHAIN_PREFIX "arm-none-eabi-")
endif()

# Set compiler
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_AR "${TOOLCHAIN_PREFIX}ar")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN_PREFIX}objdump")
set(CMAKE_SIZE "${TOOLCHAIN_PREFIX}size")

# Set path variables (relative to project root - CMAKE_SOURCE_DIR is the root)
get_filename_component(PROJECT_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)
set(STMFIRM "${PROJECT_ROOT}")
set(CMSIS "${STMFIRM}/Libraries/CMSIS")
set(STM32F4xx_StdPeriph_Driver "${STMFIRM}/Libraries/STM32F4xx_StdPeriph_Driver")
set(DISCOVERY "${STMFIRM}/Utilities/STM32F4-Discovery")
set(FREERTOS "${STMFIRM}/FreeRTOS/FreeRTOS/Source")
set(STM32_USB_Device_Library "${STMFIRM}/Libraries/STM32_USB_Device_Library")
set(STM32_USB_HOST_Library "${STMFIRM}/Libraries/STM32_USB_HOST_Library")
set(STM32_USB_OTG_Driver "${STMFIRM}/Libraries/STM32_USB_OTG_Driver")

# Common linker script
set(COMMON_LDSCRIPT "${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/stm32f4xxxg_flash.ld")

# Function to add an STM32 project
function(add_stm32_project PROJECT_NAME)
    set(options)
    set(oneValueArgs 
        HEAP_SIZE 
        STACK_SIZE 
        USE_HARD_FPU 
        MCU 
        OPTIMIZATION 
        LDSCRIPT
    )
    set(multiValueArgs
        SOURCES
        ASM_SOURCES
        INCLUDES
        DEFINES
        ASM_DEFINES
        LIBRARIES
        LIBRARY_DIRS
    )
    
    cmake_parse_arguments(PROJECT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    # Set defaults
    if(NOT PROJECT_HEAP_SIZE)
        set(PROJECT_HEAP_SIZE "8192")
    endif()
    if(NOT PROJECT_STACK_SIZE)
        set(PROJECT_STACK_SIZE "1024")
    endif()
    if(NOT PROJECT_USE_HARD_FPU)
        set(PROJECT_USE_HARD_FPU "1")
    endif()
    if(NOT PROJECT_MCU)
        set(PROJECT_MCU "cortex-m4")
    endif()
    if(NOT PROJECT_OPTIMIZATION)
        set(PROJECT_OPTIMIZATION "-O0")
    endif()
    if(NOT PROJECT_LDSCRIPT)
        set(PROJECT_LDSCRIPT "${COMMON_LDSCRIPT}")
    endif()
    
    # Create executable
    add_executable(${PROJECT_NAME}.elf ${PROJECT_SOURCES} ${PROJECT_ASM_SOURCES})
    
    # Set target properties
    set_target_properties(${PROJECT_NAME}.elf PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".elf"
    )
    
    # Common includes
    list(APPEND PROJECT_INCLUDES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMSIS}/Include"
        "${CMSIS}/Device/ST/STM32F4xx/Include"
        "${DISCOVERY}"
        "${STM32F4xx_StdPeriph_Driver}/inc"
    )
    
    # Common defines
    list(APPEND PROJECT_DEFINES
        "STM32F40_41xxx"
        "USE_STDPERIPH_DRIVER"
        "__HEAP_SIZE=${PROJECT_HEAP_SIZE}"
        "__STACK_SIZE=${PROJECT_STACK_SIZE}"
    )
    
    # FPU settings
    if(PROJECT_USE_HARD_FPU)
        list(APPEND PROJECT_DEFINES "__FPU_USED=1")
    endif()
    
    # Common compiler flags - must match Makefile exactly for binary compatibility
    target_compile_options(${PROJECT_NAME}.elf PRIVATE
        -mthumb
        -mcpu=${PROJECT_MCU}
        ${PROJECT_OPTIMIZATION}
        -g
        -gdwarf-2
        -Wall
        -Wstrict-prototypes
        -ffunction-sections
        -fdata-sections
        -fverbose-asm
    )
    
    # FPU flags
    if(PROJECT_USE_HARD_FPU)
        target_compile_options(${PROJECT_NAME}.elf PRIVATE
            -mfloat-abi=hard
            -mfpu=fpv4-sp-d16
        )
    else()
        target_compile_options(${PROJECT_NAME}.elf PRIVATE
            -mfloat-abi=soft
        )
    endif()
    
    # Add defines
    foreach(DEF ${PROJECT_DEFINES})
        target_compile_definitions(${PROJECT_NAME}.elf PRIVATE ${DEF})
    endforeach()
    
    # Add includes
    foreach(INC ${PROJECT_INCLUDES})
        target_include_directories(${PROJECT_NAME}.elf PRIVATE ${INC})
    endforeach()
    
    # Assembly flags
    set_property(TARGET ${PROJECT_NAME}.elf PROPERTY LINKER_LANGUAGE C)
    set_source_files_properties(${PROJECT_ASM_SOURCES} PROPERTIES
        COMPILE_FLAGS "-x assembler-with-cpp ${PROJECT_OPTIMIZATION} -g -gdwarf-2"
    )
    foreach(DEF ${PROJECT_ASM_DEFINES})
        set_source_files_properties(${PROJECT_ASM_SOURCES} PROPERTIES
            COMPILE_FLAGS "${CMAKE_ASM_FLAGS} -D${DEF}"
        )
    endforeach()
    
    # Linker flags - must match Makefile exactly
    target_link_options(${PROJECT_NAME}.elf PRIVATE
        -mthumb
        -mcpu=${PROJECT_MCU}
        -nostartfiles
        -T${PROJECT_LDSCRIPT}
        -Wl,-Map=${PROJECT_NAME}.map
        -Wl,--cref
        -Wl,--gc-sections
        -Wl,--no-warn-mismatch
    )
    
    # FPU linker flags
    if(PROJECT_USE_HARD_FPU)
        target_link_options(${PROJECT_NAME}.elf PRIVATE
            -mfloat-abi=hard
            -mfpu=fpv4-sp-d16
        )
    else()
        target_link_options(${PROJECT_NAME}.elf PRIVATE
            -mfloat-abi=soft
        )
    endif()
    
    # Library directories
    foreach(LIBDIR ${PROJECT_LIBRARY_DIRS})
        target_link_directories(${PROJECT_NAME}.elf PRIVATE ${LIBDIR})
    endforeach()
    
    # Libraries
    if(PROJECT_LIBRARIES)
        target_link_libraries(${PROJECT_NAME}.elf PRIVATE ${PROJECT_LIBRARIES})
    endif()
    
    # Generate hex file
    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
        COMMENT "Generating hex file: ${PROJECT_NAME}.hex"
    )
    
    # Generate binary file
    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
        COMMENT "Generating binary file: ${PROJECT_NAME}.bin"
    )
    
    # Display size information
    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
        COMMENT "Size information for ${PROJECT_NAME}.elf"
    )
    
endfunction()

# Common CMSIS sources (system_stm32f4xx.c is project-specific, not included here)
set(COMMON_CMSIS_SOURCES
    "${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c"
    "${DISCOVERY}/stm32f4_discovery.c"
)

set(COMMON_CMSIS_ASM_SOURCES
    "${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/startup_stm32f4xx.s"
)

# Common STM32F4xx peripheral driver sources
set(COMMON_STM32F4xx_SOURCES
    "${STM32F4xx_StdPeriph_Driver}/src/misc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_adc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_can.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_crc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_cryp.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_cryp_aes.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_cryp_des.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_cryp_tdes.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_dac.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_dbgmcu.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_dcmi.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_dma.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_exti.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_flash.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_fsmc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_gpio.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_hash.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_hash_md5.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_hash_sha1.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_i2c.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_iwdg.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_pwr.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_rcc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_rng.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_rtc.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_sdio.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_spi.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_syscfg.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_tim.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_usart.c"
    "${STM32F4xx_StdPeriph_Driver}/src/stm32f4xx_wwdg.c"
)

