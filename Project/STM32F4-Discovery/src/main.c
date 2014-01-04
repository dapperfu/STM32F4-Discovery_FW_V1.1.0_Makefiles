/****************************************************************************
*  Copyright (c) 2012 by Michael Fischer. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the 
*     documentation and/or other materials provided with the distribution.
*  3. Neither the name of the author nor the names of its contributors may 
*     be used to endorse or promote products derived from this software 
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
*  THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
*  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
*  SUCH DAMAGE.
*
****************************************************************************
*  History:
*
*  03.06.2012  mifi   First Version for the STM3240G-EVAL board.
*  27.12.2012  mifi   Tested with STM32F4-Discovery too.
*  04.01.2014  jafrey Added blinking LEDs to project for feedback.
****************************************************************************/
#define __MAIN_C__

#include <stdint.h>
#include <stdlib.h>
#include "stm32f4_discovery.h"

/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/
static const uint32_t d  = 7;
static const float    fd = 5.3f;
static uint32_t       dd = 8;

/* Must be 0, BSS must be cleared by the startup */
static uint32_t       must_zero_after_startup;

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/

/***************************************************************************/
/*  main                                                                   */
/***************************************************************************/
int main (void)
{
  uint32_t a  = 1;
  //uint32_t b  = 2;
  uint32_t c  = 0;
  uint32_t i  = 0;
  
  float    fa = 1.3f;
  float    fb = 2.7f;
  float    fc = 3.9f;
  
  // Initialize the LEDs
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  // Turn on LED3
  STM_EVAL_LEDOn(LED3);
  
  fa = fa + fd;
  a  = a + d + dd + must_zero_after_startup;

  // Turn on LED4
  STM_EVAL_LEDOn(LED4);
  
  /* A must be 16 here */
  if (a != 16) while (1) 
  {
	// If all failed turn on the LED6 and turn off all others.
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOn(LED6);
  }
    
  while (1)
  {
	fa=0.0f;
	fb=0.0f;
	/* 
	 * Loop this n times. The frequency of the blinking is how fast it takes to
	 * complete that many cycles. Can be used to benchmark FPU vs non-FPU
	 */
	for (i=0;i<1000000;i++) {		
		fa++;
		fb++;
		
		fa = fa + 2.6f;
		fb = fb + 1.67f;
		fc = fa + fb;
	}
	STM_EVAL_LEDToggle(LED6);
  }

  /*
   * Prevent compiler warnings
   */
  (void)fc;
  (void)c;   
  
  /*
   * This return here make no sense.
   * But to prevent the compiler warning:
   * "return type of 'main' is not 'int'
   * we use an int as return :-)
   */ 
  return(0);
}

/*** EOF ***/
