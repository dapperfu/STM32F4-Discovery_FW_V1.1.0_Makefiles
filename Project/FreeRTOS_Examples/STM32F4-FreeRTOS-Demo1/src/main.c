/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **                STMicroelectronics STM32F4xx Standard Peripherals Library
 **
 **  Distribution: The file is distributed as is, without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 **
 *****************************************************************************
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "utils.h"
#include "debug.h"
#include "mems.h"

// Task priorities: Higher numbers are higher priority.
#define mainTIME_TASK_PRIORITY      ( tskIDLE_PRIORITY + 3 )
#define mainMEMS_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2 )
#define mainDEBUG_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define mainINTEGER_TASK_PRIORITY   ( tskIDLE_PRIORITY )

xTaskHandle hTimeTask;
xTaskHandle hMemsTask;
xTaskHandle hDebugTask;

portTASK_FUNCTION_PROTO( vTimeTask, pvParameters );
portTASK_FUNCTION_PROTO( vMemsTask, pvParameters );
portTASK_FUNCTION_PROTO( vDebugTask, pvParameters );

uint64_t u64Ticks=0;        // Counts OS ticks (default = 1000Hz).
uint64_t u64IdleTicks=0;    // Value of u64IdleTicksCnt is copied once per sec.
uint64_t u64IdleTicksCnt=0; // Counts when the OS has no task to execute.
uint16_t u16PWM1=0;

// ============================================================================
int main( void ) {

    HwInit();

    vDebugInitQueue();
	vDebugPrintf( "\r\nEPS Test1 0.0.1 - 1/4/2012\r\n" );
	vDebugPrintResetType();

    // Tasks get started here...
    xTaskCreate( vTimeTask, (signed char *) "TIME", configMINIMAL_STACK_SIZE, 
            NULL, mainTIME_TASK_PRIORITY, &hTimeTask );
    xTaskCreate( vMemsTask, (signed char *) "MEMS", configMINIMAL_STACK_SIZE, 
            NULL, mainMEMS_TASK_PRIORITY, &hMemsTask );
    xTaskCreate( vDebugTask, (signed char *) "DEBUG", configMINIMAL_STACK_SIZE,
            NULL, mainDEBUG_TASK_PRIORITY, &hDebugTask );

    vTaskStartScheduler(); // This should never return.

    // Will only get here if there was insufficient memory to create
    // the idle task.
    for( ;; );  
}

// This task should run every 50ms.  The task will average 50ms over time by
// monitoring the actual time between calls and self adjusting accordingly.
// ---------------------------------------------------------------------------- 
portTASK_FUNCTION( vTimeTask, pvParameters ) {
    portTickType xLastWakeTime;
    uint8_t i=0;

    xLastWakeTime = xTaskGetTickCount();

    for(;;) {
        // Once per second, copy the number of idle ticks and then
        // reset the rolling counter.
        if ( ++i == 20 ) {
            i = 0;
            u64IdleTicks = u64IdleTicksCnt;
            u64IdleTicksCnt = 0;
        }

        vTaskDelayUntil( &xLastWakeTime, ( 50 / portTICK_RATE_MS ) );
    }
}

// This FreeRTOS callback function gets called once per tick (default = 1000Hz).
// ---------------------------------------------------------------------------- 
void vApplicationTickHook( void ) {
    ++u64Ticks;
}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ---------------------------------------------------------------------------- 
void vApplicationIdleHook( void ) {
    ++u64IdleTicksCnt;
}

// A required FreeRTOS function.
// ---------------------------------------------------------------------------- 
void vApplicationMallocFailedHook( void ) {
    configASSERT( 0 );  // Latch on any failure / error.
}




