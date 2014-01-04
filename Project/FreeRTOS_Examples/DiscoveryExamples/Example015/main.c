/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    This is example #15 from the book Using the FreeRTOS Real Time Kernel - A Practical Guide

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* CMSIS / hardware includes */
#include "system_stm32f4xx.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "debug.h"

/* Dimensions the buffer into which messages destined for stdout are placed. */
#define mainMAX_MSG_LEN	(80)

/* The task to be created.  Two instances of this task are created. */
static void prvPrintTask(void *pvParameters);

/* The function that uses a mutex to control access to standard out. */
static void prvNewPrintString(const portCHAR *pcString);

/*-----------------------------------------------------------*/

/* Declare a variable of type xSemaphoreHandle.  This is used to reference the
mutex type semaphore that is used to ensure mutual exclusive access to stdout. */
xSemaphoreHandle xMutex;


int main(void)
{
	/* System Initialization. */
	SystemInit();
	SystemCoreClockUpdate();
	// Create the debug task & print example number and system core clock.
	vDebugInit(15);

    /* Before a semaphore is used it must be explicitly created.  In this example
	a mutex type semaphore is created. */
    xMutex = xSemaphoreCreateMutex();

	/* The tasks are going to use a pseudo random delay, seed the random number
	generator. */
	srand(567);

	/* Only create the tasks if the semaphore was created successfully. */
	if(xMutex != NULL)
	{
		/* Create two instances of the tasks that attempt to write stdout.  The
		string they attempt to write is passed in as the task parameter.  The tasks
		are created at different priorities so some pre-emption will occur. */
		xTaskCreate(prvPrintTask, (const signed char * const)"Print1", 240, "Task 1 ******************************************\r\n", 1, NULL);
		xTaskCreate(prvPrintTask, (const signed char * const)"Print2", 240, "Task 2 ------------------------------------------\r\n", 2, NULL);

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
	}

    /* If all is well we will never reach here as the scheduler will now be
    running the tasks.  If we do reach here then it is likely that there was
    insufficient heap memory available for a resource to be created. */
	while(1);
}
/*-----------------------------------------------------------*/

static void prvNewPrintString(const portCHAR *pcString)
{
static char cBuffer[ mainMAX_MSG_LEN ];

	/* The semaphore is created before the scheduler is started so already
	exists by the time this task executes.

	Attempt to take the semaphore, blocking indefinitely if the mutex is not
	available immediately.  The call to xSemaphoreTake() will only return when
	the semaphore has been successfully obtained so there is no need to check the
	return value.  If any other delay period was used then the code must check
	that xSemaphoreTake() returns pdTRUE before accessing the resource (in this
	case standard out. */
	xSemaphoreTake(xMutex, portMAX_DELAY);
	{
		/* The following line will only execute once the semaphore has been
		successfully obtained - so standard out can be accessed freely. */
		sprintf(cBuffer, "%s", pcString);
		vDebugPrintf(cBuffer);
	}
	xSemaphoreGive(xMutex);
}
/*-----------------------------------------------------------*/

static void prvPrintTask(void *pvParameters)
{
	(void)pvParameters;
char *pcStringToPrint;

	/* Two instances of this task are created so the string the task will send
	to prvNewPrintString() is passed in the task parameter.  Cast this to the
	required type. */
	pcStringToPrint = (char *) pvParameters;

	while(1)
	{
		/* Print out the string using the newly defined function. */
		prvNewPrintString(pcStringToPrint);

		/* Wait a pseudo random time.  Note that rand() is not necessarily
		re-entrant, but in this case it does not really matter as the code does
		not care what value is returned.  In a more secure application a version
		of rand() that is known to be re-entrant should be used - or calls to
		rand() should be protected using a critical section. */
		vTaskDelay((rand() & 0x1FF));
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining - and
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
	while(1);
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	(void)pxTask;
	(void)pcTaskName;
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
	is set to either 1 or 2 in FreeRTOSConfig.h. */
	while(1);
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
	FreeRTOSConfig.h. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}
