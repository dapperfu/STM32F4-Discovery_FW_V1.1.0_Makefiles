# STM32F4-Demonstration project
add_stm32_project(STM32F4-Discovery_Demo
    HEAP_SIZE 8192
    STACK_SIZE 1024
    SOURCES
        main.c
        selftest.c
        stm32f4xx_it.c
        system_stm32f4xx.c
        usb_bsp.c
        usbd_desc.c
        usbd_usr.c
        ${DISCOVERY}/stm32f4_discovery.c
        ${DISCOVERY}/stm32f4_discovery_audio_codec.c
        ${DISCOVERY}/stm32f4_discovery_lis302dl.c
        ${COMMON_STM32F4xx_SOURCES}
        ${STM32_USB_Device_Library}/Core/src/usbd_core.c
        ${STM32_USB_Device_Library}/Core/src/usbd_ioreq.c
        ${STM32_USB_Device_Library}/Core/src/usbd_req.c
        ${STM32_USB_Device_Library}/Class/hid/src/usbd_hid_core.c
        ${STM32_USB_OTG_Driver}/src/usb_core.c
        ${STM32_USB_OTG_Driver}/src/usb_dcd.c
        ${STM32_USB_OTG_Driver}/src/usb_dcd_int.c
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    INCLUDES
        ${STM32_USB_Device_Library}/Class/hid/inc
        ${STM32_USB_Device_Library}/Core/inc
        ${STM32_USB_OTG_Driver}/inc
    DEFINES
        USE_USB_OTG_FS
)

