cmake_minimum_required(VERSION 3.15)
project(STM32F4-Discovery_FW_V1.1.0_Makefiles C ASM)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Include common STM32 configuration
include(cmake/STM32Common.cmake)

# Add all projects
add_subdirectory(Project)

