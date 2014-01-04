/*
 * debug.h
 *
 *  Created on: Feb 9, 2011
 *      Author: James
 */

#ifndef DEBUG_H_
#define DEBUG_H_

void vDebugInit(int exampleNum);
void vDebugInitQueue( void );
void vDebugTask(void *pvParameters );
void vDebugString( char *s );
void vDebugPrintf(const char *fmt, ...);
void vDebugPrintResetType( void );

#define mainDEBUG_TASK_PRIORITY     (tskIDLE_PRIORITY + 10)

#endif /* DEBUG_H_ */
