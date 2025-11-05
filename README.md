# STM32F4-Discovery FW v1.1.0 Makefiles

This project is intended to provide makefiles for use with STM32F4-Discovery FW v1.1.0  which can be downloaded from the ST website: http://www.st.com/web/en/catalog/tools/PF257904#

ST Micro provides projects for EWARM, MDK-ARM and TrueSTUDIO. However these are all commercial IDEs and possibly unaffordable for the home tinkerer. This project was created to provide makefiles for each of the provided Projects.

This is my first foray into Makefile programming. If you have any suggestions or comments please feel free to submit them to the issues list.

https://github.com/jed-frey/STM32F4-Discovery_FW_V1.1.0_Makefiles/issues

# Requirements

- ARM toolchain: https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain

**Note:** Make sure to download the none-eabi files for your platform.

Adding to your path:

Where "/opt/gcc-arm-none-eabi/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi" is where the toolchain is extracted

Temporary:

    export PATH=${PATH}:/opt/gcc-arm-none-eabi/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin

Permanently, put the above in your ```.bashrc``` file.

You should now be able to run ```arm-none-eabi-gcc```:

```
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc (GNU Tools for Arm Embedded Processors 9-2019-q4-major) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

# Usage

### Cloning Repository:

    git clone https://github.com/jed-frey/STM32F4-Discovery_FW_V1.1.0_Makefiles.git

### Building All Projects

    cd STM32F4-Discovery_FW_V1.1.0_Makefiles/Project
    make

```make``` is recursive, digging through all the subdirectories and executing them if they have a ```Makefile```

### Build Specific Project

    cd STM32F4-Discovery_FW_V1.1.0_Makefiles/Project/Peripheral_Examples/IO_Toggle
    make