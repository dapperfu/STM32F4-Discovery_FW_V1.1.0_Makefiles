/*
 * debug.c
 *
 *  Created on: Jan. 5, 2012
 *      Author: James Kemp
 */
#include <stdarg.h>
#include <ctype.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "debug.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "debug.h"
#include "utils.h"
#include "mems.h"

// Private functions.
void vNum2String(char *s, uint8_t *pPos, uint32_t u32Number, uint8_t u8Base);

// Total buffer size for all debug messages.
#define DEBUG_QUEUE_SIZE	1024
xQueueHandle xDebugQueue;

extern xTaskHandle hDebugTask;

void vDebugInit(int exampleNum) {	
	vUSART2_Init();
	vDebugInitQueue();
	xTaskCreate((pdTASK_CODE)vDebugTask, (const signed char * const)"DEBUG", (unsigned short)configMINIMAL_STACK_SIZE, NULL, (unsigned portBASE_TYPE)mainDEBUG_TASK_PRIORITY, (xTaskHandle)NULL);
	// Clear the screen.
	vDebugPrintf("\e[2J\e[H");
	vDebugPrintf("Example: %d\r\n",exampleNum);
	vDebugPrintf("System Core Clock is running at: %dMHz\r\n",SystemCoreClock/1000000);
}
// ============================================================================
void vDebugInitQueue(void) {
	xDebugQueue = xQueueCreate(DEBUG_QUEUE_SIZE, sizeof(char));
}

// ============================================================================
void vDebugTask(void *pvParameters) {
	char ch;
	portBASE_TYPE xStatus;
	//uint16_t u16StackSize;

	/* The parameters are not used. */
	(void) pvParameters;

	vDebugString("Debug task started.\r\n");

	while(1) {
		// As long as there are characters in the queue fifo this code should
		// pop them out and send them as quick as possible out the UART.
		if(USART_GetFlagStatus(USART2, USART_FLAG_TXE)) {
			// We don't want to block forever - need to check on Rx too.
			xStatus = xQueueReceive(xDebugQueue, &ch, 10 / portTICK_RATE_MS);
			if(xStatus == pdPASS) USART_SendData(USART2, ch);
		}
		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)) {
			ch = USART_ReceiveData(USART2);
			// Handle Debug Console Commands Here.
			switch (ch) {

			// Alphabetical list of commands the console debugger responds to.

			case 'm':
				vDebugPrintf("Mems dump Stopped.\r\n");
				//vSetMemsDump(false);
				break;
			case 'M':
				vDebugPrintf("Mems dump Started.\r\n");
				//vSetMemsDump(true);
				break;

			case 'a':
				vDebugPrintf("AtoD dump Stopped.\r\n");
				//vSetAtoDDump(FALSE);
				break;
			case 'A':
				vDebugPrintf("AtoD dump Started.\r\n");
				//vSetAtoDDump(TRUE);
				break;

			// Print out how much stack space remains on each task stack.
			case 's':
				vDebugPrintf("Remaining space on Task Stack:\r\n");
				break;

			// Add general test code here...
			case 't':
				break;

			default:
				break;
			}
		}

		taskYIELD();
	}
}



// This function copies the the given string into the OS queue.  If the queue
// is full then the rest of the string is ignored.
// ToDo: Ignoring a full queue is not good.
// ============================================================================
void vDebugString(char *s) {
	portBASE_TYPE xStatus;
	while (*s) {
		xStatus = xQueueSendToBack(xDebugQueue, s++, 0);
		if (xStatus == errQUEUE_FULL) break;
	}
}

// Simply print to the debug console a string based on the type of reset.
// ============================================================================
void vDebugPrintResetType(void) {

	if (PWR_GetFlagStatus(PWR_FLAG_WU))
		vDebugPrintf("PWR: Wake Up flag\r\n");
	if (PWR_GetFlagStatus(PWR_FLAG_SB))
		vDebugPrintf("PWR: StandBy flag.\r\n");
	if (PWR_GetFlagStatus(PWR_FLAG_PVDO))
		vDebugPrintf("PWR: PVD Output.\r\n");
	if (PWR_GetFlagStatus(PWR_FLAG_BRR))
		vDebugPrintf("PWR: Backup regulator ready flag.\r\n");
	if (PWR_GetFlagStatus(PWR_FLAG_REGRDY))
		vDebugPrintf("PWR: Main regulator ready flag.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_BORRST))
		vDebugPrintf("RCC: POR/PDR or BOR reset\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_PINRST))
		vDebugPrintf("RCC: Pin reset.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_PORRST))
		vDebugPrintf("RCC: POR/PDR reset.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_SFTRST))
		vDebugPrintf("RCC: Software reset.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST))
		vDebugPrintf("RCC: Independent Watchdog reset.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST))
		vDebugPrintf("RCC: Window Watchdog reset.\r\n");
	if (RCC_GetFlagStatus(RCC_FLAG_LPWRRST))
		vDebugPrintf("RCC: Low Power reset.\r\n");
}



// DebugPrintf - really trivial implementation, however, it's reentrant!
// ToDo - This needs a rewrite! Add code to check we're not overflowing.
// ============================================================================
void vDebugPrintf(const char *fmt, ...) {
	char sTmp[80];	// String build area.  String lives on the stack!
	uint8_t pos=0;
	char *bp = (char *)fmt;
    va_list ap;
    char c;
    char *p;
    int i;

    va_start(ap, fmt);

    while ((c = *bp++)) {
        if (c != '%') {
            sTmp[pos++] = c;
            continue;
        }

        switch ((c = *bp++)) {
			// d - decimal value
			case 'd':
				vNum2String(sTmp, &pos, va_arg(ap, uint32_t), 10);
				break;

			// %x - value in hex
			case 'x':
				sTmp[pos++] = '0';
				sTmp[pos++] = 'x';
				vNum2String(sTmp, &pos, va_arg(ap, uint32_t), 16);
				break;

			// %b - binary
			case 'b':
				sTmp[pos++] = '0';
				sTmp[pos++] = 'b';
				vNum2String(sTmp, &pos, va_arg(ap, uint32_t), 2);
				break;

			// %c - character
			case 'c':
				sTmp[pos++] = va_arg(ap, int);
				break;

			// %i - integer
			case 'i':
				i = va_arg(ap, int32_t);
				if(i < 0){
					sTmp[pos++] = '-';
					vNum2String(sTmp, &pos, (~i)+1, 10);
				} else {
					vNum2String(sTmp, &pos, i, 10);
				}
				break;

			// %s - string
			case 's':
				p = va_arg(ap, char *);
				do {
					sTmp[pos++] = *p++;
				} while (*p);
				break;

			// %% - output % character
			case '%':
				sTmp[pos++] = '%';
				break;

			// Else, must be something else not handled.
			default:
				sTmp[pos++] = '?';
				break;
        }
    }
    sTmp[pos++] = 0;		// Mark the end of the string.
    vDebugString(sTmp);	// Copy the string into the OS queue.
    return;
}


// Convert a number to a string - used in vDebugPrintf.
// ============================================================================
void vNum2String(char *s, uint8_t *pPos, uint32_t u32Number, uint8_t u8Base) {

    char buf[33];
    char *p = buf + 33;
    uint32_t c, n;

    *--p = '\0';
    do {
        n = u32Number / u8Base;
        c = u32Number - (n * u8Base);
        if (c < 10) {
            *--p = '0' + c;
        } else {
            *--p = 'a' + (c - 10);
        }
        u32Number /= u8Base;
    } while (u32Number != 0);

    while (*p){
    	s[ *pPos ] = *p;
    	*pPos += 1;
        p++;
    }
    return;
}



