/*
 * utils.c
 *
 *  Created on: Jan 1, 2012
 *      Author: James
 */

#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "utils.h"

#include <stdarg.h>
#include <ctype.h>


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 333;
uint16_t CCR2_Val = 249;
uint16_t CCR3_Val = 166;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;

const uint16_t uc16PercentToPWM[100] = {
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6, 6, 7, 9, 10, 11, 13, 14, 16, 18,
	20, 22, 24, 26, 29, 31, 34, 37, 40, 43, 46, 49, 53, 57, 61, 65, 69, 73, 78, 82, 87,
	92, 98, 103, 109, 114, 120, 126, 133, 139, 146, 153, 160, 167, 175, 183, 191, 199,
	207, 216, 225, 234, 243, 252, 262, 272, 282, 292, 303, 314, 325, 336, 348, 359, 371,
	384, 396, 409, 422, 435, 449, 463, 477, 491, 506, 520, 535, 551, 566, 582, 599, 615,
	632, 649, 666
};

// ----------------------------------------------------------------------------
uint16_t ptopwm( uint8_t p ) {
	return uc16PercentToPWM[ MIN( p, 99 )];
}

// ----------------------------------------------------------------------------
void HwInit( void ) {
    SystemCoreClockUpdate( );
    // Make sure SysTick is running at a 1ms rate.
    if ( SysTick_Config( SystemCoreClock / 1000 ) ) {
        /* Capture error */
        while ( 1 );
    }
    // SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK_Div8 );

    /* Initialize Leds mounted on STM32F4-Discovery board */
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);

    /* Turn on LED4 and LED5 */
    STM_EVAL_LEDOn(LED4);
    STM_EVAL_LEDOn(LED5);

    /*
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init( GPIOD, &GPIO_InitStructure );
	*/

    /* TIM Configuration */
    TIM3_Config();
    TIM4_Config();

    /* -----------------------------------------------------------------------
       TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles.

       In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1), 
       since APB1 prescaler is different from 1.   
       TIM3CLK = 2 * PCLK1  
       PCLK1 = HCLK / 4 
       => TIM3CLK = HCLK / 2 = SystemCoreClock /2

       To get TIM3 counter clock at 28 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = ((SystemCoreClock /2) /28 MHz) - 1

       To get TIM3 output clock at 30 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM3 counter clock / TIM3 output clock) - 1
       = 665

       TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
       TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
       TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
       TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%

Note: 
SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
function to update SystemCoreClock variable value. Otherwise, any configuration
based on this variable will be incorrect.    
----------------------------------------------------------------------- */  

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 665;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );
    TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init( TIM3, &TIM_OCInitStructure );
    TIM_OC1Init( TIM4, &TIM_OCInitStructure );

    TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );
    TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Enable );

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

    TIM_OC2Init( TIM3, &TIM_OCInitStructure );
    TIM_OC2Init( TIM4, &TIM_OCInitStructure );

    TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable );
    TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Enable );

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

    TIM_OC3Init( TIM3, &TIM_OCInitStructure );
    TIM_OC3Init( TIM4, &TIM_OCInitStructure );

    TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable );
    TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Enable );

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

    TIM_OC4Init( TIM3, &TIM_OCInitStructure );
    TIM_OC4Init( TIM4, &TIM_OCInitStructure );

    TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable );
    TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Enable );

    TIM_ARRPreloadConfig( TIM3, ENABLE );
    TIM_ARRPreloadConfig( TIM4, ENABLE );

    /* TIM3 enable counter */
    TIM_Cmd( TIM3, ENABLE );
    TIM_Cmd( TIM4, ENABLE );

    vUSART2_Init();   // Start up UART2
}

/**
 * @brief  Configure the TIM3 Ouput Channels.
 * @param  None
 * @retval None
 */
// ----------------------------------------------------------------------------
void TIM3_Config( void ) {

    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

    /* GPIOC and GPIOB clock enable */
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE );

    /* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init( GPIOC, &GPIO_InitStructure ); 

    /* GPIOB Configuration:  TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init( GPIOB, &GPIO_InitStructure ); 

    /* Connect TIM3 pins to AF2 */  
    GPIO_PinAFConfig( GPIOC, GPIO_PinSource6, GPIO_AF_TIM3 );
    GPIO_PinAFConfig( GPIOC, GPIO_PinSource7, GPIO_AF_TIM3 ); 
    GPIO_PinAFConfig( GPIOB, GPIO_PinSource0, GPIO_AF_TIM3 );
    GPIO_PinAFConfig( GPIOB, GPIO_PinSource1, GPIO_AF_TIM3 ); 
}

/**
 * @brief  Configure the TIM4 Ouput Channels.
 * @param  None
 * @retval None
 */
// ----------------------------------------------------------------------------
void TIM4_Config( void ) {

    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );

    /* GPIOD clock enable */
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );

    /* GPIOD Configuration: TIM4 CH1 (PD12) and TIM3 CH2 (PD13) */
    /* GPIOD Configuration: TIM4 CH3 (PD14) and TIM4 CH4 (PD15) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init( GPIOD, &GPIO_InitStructure ); 

    /* Connect TIM4 pins to AF2 */  
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource12, GPIO_AF_TIM4 );
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource13, GPIO_AF_TIM4 ); 
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource14, GPIO_AF_TIM4 );
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource15, GPIO_AF_TIM4 ); 
}

// TIMx_SetDuty provides a quick method of changing the PWM match register.
// Using the bitfield, multiple channels can be set to the save value within a timer.
// ----------------------------------------------------------------------------
void TIM_SetDuty( TIM_TypeDef* TIMx, uint8_t chan_bitfield, uint16_t duty ) {
    if ( chan_bitfield & 0x01 ) TIMx->CCR1 = duty;
    if ( chan_bitfield & 0x02 ) TIMx->CCR2 = duty;
    if ( chan_bitfield & 0x04 ) TIMx->CCR3 = duty;
    if ( chan_bitfield & 0x08 ) TIMx->CCR4 = duty;
}


// ============================================================================
void vUSART2_Init( void ) {
    USART_ClockInitTypeDef USART_ClockInitStruct;
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable needed clocks for uart.
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );

    // Make sure you use 'GPIO_PinSource2' and NOT 'GPIO_Pin_2'.  Using the
    // latter will not work!
    GPIO_PinAFConfig( GPIOA, GPIO_PinSource2, GPIO_AF_USART2 );
    GPIO_PinAFConfig( GPIOA, GPIO_PinSource3, GPIO_AF_USART2 );

    // Setup Tx / Rx pins.
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			// Tx Pin
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( GPIOA, &GPIO_InitStructure );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			// Rx Pin
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    // Make sure syncro clock is turned off.
    USART_ClockStructInit( &USART_ClockInitStruct );
    USART_ClockInit( USART2, &USART_ClockInitStruct  );

    // Setup transmit complete irq.
    USART_ITConfig( USART2, USART_IT_TC, ENABLE );

    // Use defaults (except baud rate).
    USART_StructInit( &USART_InitStructure );
    USART_InitStructure.USART_BaudRate = 115200;
    USART_Init( USART2, &USART_InitStructure );
    USART_Cmd( USART2, ENABLE );

    // Enable USART2 interrupt.
    /*
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    */
}





