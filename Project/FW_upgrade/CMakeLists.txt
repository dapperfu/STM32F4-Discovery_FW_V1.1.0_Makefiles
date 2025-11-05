# FW_upgrade project
add_stm32_project(FW_upgrade
    HEAP_SIZE 8192
    STACK_SIZE 2048
    SOURCES
        src/main.c
        src/stm32f4xx_it.c
        src/system_stm32f4xx.c
        src/usb_bsp.c
        src/usbh_usr.c
        src/command.c
        src/flash_if.c
        ${CMSIS}/Device/ST/STM32F4xx/Source/Templates/gcc_none_eabi/syscalls.c
        ${DISCOVERY}/stm32f4_discovery.c
        ${COMMON_STM32F4xx_SOURCES}
        ${STM32_USB_HOST_Library}/Core/src/usbh_core.c
        ${STM32_USB_HOST_Library}/Core/src/usbh_ioreq.c
        ${STM32_USB_HOST_Library}/Core/src/usbh_stdreq.c
        ${STM32_USB_HOST_Library}/Core/src/usbh_hcs.c
        ${STM32_USB_HOST_Library}/Class/MSC/src/usbh_msc_core.c
        ${STM32_USB_HOST_Library}/Class/MSC/src/usbh_msc_bot.c
        ${STM32_USB_HOST_Library}/Class/MSC/src/usbh_msc_scsi.c
        ${STM32_USB_HOST_Library}/Class/MSC/src/usbh_msc_fatfs.c
        ${STM32_USB_OTG_Driver}/src/usb_core.c
        ${STM32_USB_OTG_Driver}/src/usb_hcd.c
        ${STM32_USB_OTG_Driver}/src/usb_hcd_int.c
        ${STM32_USB_OTG_Driver}/src/usb_otg.c
    ASM_SOURCES
        ${COMMON_CMSIS_ASM_SOURCES}
    INCLUDES
        inc
    DEFINES
        USE_USB_OTG_FS
)

