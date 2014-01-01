/*
 * FreeRTOS+FAT FS V1.0.0 (C) 2013 HCC Embedded
 *
 * The FreeRTOS+FAT SL license terms are different to the FreeRTOS license 
 * terms.
 * 
 * FreeRTOS+FAT SL uses a dual license model that allows the software to be used 
 * under a standard GPL open source license, or a commercial license.  The 
 * standard GPL license (unlike the modified GPL license under which FreeRTOS 
 * itself is distributed) requires that all software statically linked with 
 * FreeRTOS+FAT SL is also distributed under the same GPL V2 license terms.  
 * Details of both license options follow:
 * 
 * - Open source licensing -
 * FreeRTOS+FAT SL is a free download and may be used, modified, evaluated and
 * distributed without charge provided the user adheres to version two of the 
 * GNU General Public License (GPL) and does not remove the copyright notice or 
 * this text.  The GPL V2 text is available on the gnu.org web site, and on the
 * following URL: http://www.FreeRTOS.org/gpl-2.0.txt.
 * 
 * - Commercial licensing -
 * Businesses and individuals who for commercial or other reasons cannot comply
 * with the terms of the GPL V2 license must obtain a commercial license before 
 * incorporating FreeRTOS+FAT SL into proprietary software for distribution in 
 * any form.  Commercial licenses can be purchased from 
 * http://shop.freertos.org/fat_sl and do not require any source files to be 
 * changed.
 *
 * FreeRTOS+FAT SL is distributed in the hope that it will be useful.  You
 * cannot use FreeRTOS+FAT SL unless you agree that you use the software 'as
 * is'.  FreeRTOS+FAT SL is provided WITHOUT ANY WARRANTY; without even the
 * implied warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. Real Time Engineers Ltd. and HCC Embedded disclaims all
 * conditions and terms, be they implied, expressed, or statutory.
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/FreeRTOS-Plus
 *
 */

#ifndef _PSP_FAT_FAT_SL_H
#define _PSP_FAT_FAT_SL_H

#include <stdint.h>
#include "../../../psp/include/psp_string.h"

#include "../../../version/ver_fat_sl.h"
#if VER_FAT_SL_MAJOR != 3
 #error Incompatible FAT_SL version number!
#endif
#include "../../../version/ver_psp_fat_sl.h"
#if VER_PSP_FAT_FAT_SL_MAJOR != 1 || VER_PSP_FAT_FAT_SL_MINOR != 1
 #error Incompatible PSP_FAT_FAT_SL version number!
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t  all_tests_passed;

/* Use to display text (printf). */
void _f_dump ( char * s );

/* Use to display test result (printf). */
uint8_t _f_result ( uint8_t testnum, uint32_t result );

/* Use to build file system (mount). */
uint8_t _f_poweron ( void );

#ifdef __cplusplus
}
#endif


#endif /* _PSP_FAT_FAT_SL_H */
