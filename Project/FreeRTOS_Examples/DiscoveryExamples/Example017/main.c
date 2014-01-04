//
//	This FreeRTOS example started life as a demo from Finn Bindeballe's FreeRTOS v7.1.1 port.
//
//	This is now example #17.
//
//	It is now targeted to the following:
//	Tool/System		Manufacturer				Version
//	IDE:			Rowley Associates			CrossWorks v2.3
//	RTOS:			Real Time Engineers, Ltd.	FreeRTOS v7.3.0
//	Processor:		STMicroelectronics			STM32F407VG
//	Board:			STMicroelectronics			STM32F4-discovery
//
//    1 tab == 4 spaces!
//
//	FreeRTOS Information:
//		http://www.FreeRTOS.org - Documentation, latest information, license and
//		contact details.
//
//		http://www.SafeRTOS.com - A version that is certified for use in safety
//		critical systems.
//
//		http://www.OpenRTOS.com - Commercial support, development, porting,
//		licensing and training services.
//

#include <stdio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "debug.h"
#include "utils.h"

#define	TASK_LOOP	for (;;)

static void trace(const char* str)
{
	vTaskSuspendAll();
	vDebugPrintf(str);
	xTaskResumeAll();
}

//
//	Orange LED (Port D, pin 13)
//
static void LED_orange(void *pvParameters)
{
	(void)pvParameters;
	trace("Task: LED_orange started\r\n");
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);

	TASK_LOOP {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		vTaskDelay(50 / portTICK_RATE_MS);
	}
}

//
//	Green LED (Port D, pin 12)
//
static void LED_green(void *pvParameters)
{
	(void)pvParameters;
	trace("Task: LED_green started\r\n");
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);

	TASK_LOOP {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(60 / portTICK_RATE_MS);
	}
}

//
//	Red LED (Port D, pin 13)
//
static void LED_red(void *pvParameters)
{
	(void)pvParameters;
	trace("Task: LED_red started\r\n");
	GPIO_ResetBits(GPIOD, GPIO_Pin_14);

	TASK_LOOP {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		vTaskDelay(70 / portTICK_RATE_MS);
	}
}

//
//	Blue LED (Port D, pin 13)
//
static void LED_blue(void *pvParameters)
{
	(void)pvParameters;
	trace("Task: LED_blue started\r\n");
	GPIO_ResetBits(GPIOD, GPIO_Pin_15);

	TASK_LOOP {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(80 / portTICK_RATE_MS);
	}
}

static void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void)
{
	/* System Initialization. */
	SystemInit();
	SystemCoreClockUpdate();
	// Create the debug task & print example number and system core clock.
	vDebugInit(17);
	IO_Init();
	
	xTaskCreate(LED_orange, (signed char*)"Orange", 128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(LED_green,  (signed char*)"Green",  128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(LED_red,    (signed char*)"Red",    128, NULL, tskIDLE_PRIORITY+1, NULL);
	xTaskCreate(LED_blue,   (signed char*)"Blue",   128, NULL, tskIDLE_PRIORITY+1, NULL);
	//vDebugPrintf("Scheduler started\r\n");
	vTaskStartScheduler();
	return (int)NULL;
}
