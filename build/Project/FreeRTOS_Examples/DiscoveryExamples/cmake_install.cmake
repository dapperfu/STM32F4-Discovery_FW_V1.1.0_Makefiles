# Install script for directory: /projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/Project/FreeRTOS_Examples/DiscoveryExamples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/gcc-arm-none-eabi/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example001/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example002/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example003/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example004/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example005/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example006/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example007/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example008/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example009/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example010/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example011/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example012/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example013/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example014/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example015/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example016/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/Example017/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/projects/STM32F4-Discovery_FW_V1.1.0_Makefiles/build/Project/FreeRTOS_Examples/DiscoveryExamples/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
