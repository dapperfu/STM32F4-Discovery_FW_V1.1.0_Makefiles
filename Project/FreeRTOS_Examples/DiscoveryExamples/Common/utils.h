/*
 * utils.h
 *
 *  Created on: Jan 1, 2012
 *      Author: James
 */

#ifndef UTILS_H_
#define UTILS_H_

void HwInit( void );
void TIM3_Config(void);
void TIM4_Config(void);
void TIM_SetDuty(TIM_TypeDef* TIMx, uint8_t chan_bitfield, uint16_t duty);
void vUSART2_Init(void);
uint16_t ptopwm(uint8_t p);

#define DOUBLECLICK_Z                    ((uint8_t)0x60)
#define SINGLECLICK_Z                    ((uint8_t)0x50)

/* TIM2 Autoreload and Capture Compare register values */
#define TIM_ARR                          ((uint16_t)1900)
#define TIM_CCR                          ((uint16_t)1000)

#define ABS(x)                           (x < 0) ? (-x) : x
#define MAX(a,b)                         (a < b) ? (b) : a
#define MIN(a,b)                         (a < b) ? (a) : b

#ifndef false
#define false 0
#endif

#ifndef true
#define true !false
#endif

#endif /* UTILS_H_ */
