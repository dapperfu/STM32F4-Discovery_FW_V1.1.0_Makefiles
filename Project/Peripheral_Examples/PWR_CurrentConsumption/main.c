/*$T indentinput.cpp GC 1.140 01/08/14 08:29:58 */

/*
 * @file PWR_CurrentConsumption/main.c @author MCD Application Team @version
 * V1.0.0 @date 19-September-2011 @brief Main program body @attention THE PRESENT
 * FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING
 * INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A
 * RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF
 * SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS. <h2><center>&copy;
 * COPYRIGHT 2011 STMicroelectronics</center></h2> ;
 * Includes
 */
#include "stm32f4_discovery.h"
#include "stm32f4xx_lp_modes.h"

/*
 * @addtogroup STM32F4_Discovery_Peripheral_Examples @{ ;
 * @addtogroup PWR_CurrentConsumption @{ ;
 * Private typedef ;
 * Private define ;
 * Private macro ;
 * Private variable
 */
__IO uint32_t	i = 0;
__IO uint8_t	UserButtonStatus = 0;

/*
 =======================================================================================================================
    Private function prototypes ;
    Private functions ;
    @brief Main program @param None @retval None
 =======================================================================================================================
 */
int main(void)
{

	/*
	 * !< At this stage the microcontroller clock setting is already configured, this
	 * is done through SystemInit() function which is called from startup file
	 * (startup_stm32f4xx.s) before to branch to application main. To reconfigure the
	 * default setting of SystemInit() function, refer to system_stm32f4xx.c file ;
	 * Enable PWR APB1 Clock
	 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to Backup */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset RTC Domain */
	RCC_BackupResetCmd(ENABLE);
	RCC_BackupResetCmd(DISABLE);

	/* Configure User Button */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

	/* Initialize LEDs on STM32F4-Discovery board */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);

	/* Wait until User button is pressed to enter the Low Power mode */
	while (STM_EVAL_PBGetState(BUTTON_USER) == RESET)
		{
			STM_EVAL_LEDOff(LED3);
			STM_EVAL_LEDOff(LED4);
		}

	/* Loop while User button is maintained pressed */
	while (STM_EVAL_PBGetState(BUTTON_USER) != RESET)
		{
			STM_EVAL_LEDOn(LED3);
			STM_EVAL_LEDOn(LED4);
		}

	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
#if defined(SLEEP_MODE)

	/*
	 * Sleep Mode Entry - System Running at PLL (168MHz) - Flash 3 wait state -
	 * Prefetch and Cache enabled - Code running from Internal FLASH - All peripherals
	 * disabled. - Wakeup using EXTI Line (User Button PA.00
	 */
	SleepMode_Measure();
#elif defined(STOP_MODE)
	/*
	 * STOP Mode Entry - RTC Clocked by LSI - Regulator in LP mode - HSI, HSE OFF and
	 * LSI OFF if not used as RTC Clock source - No IWDG - FLASH in deep power down
	 * mode - Automatic Wakeup using RTC clocked by LSI (after ~20s)
	 */
	StopMode_Measure();
#elif defined(STANDBY_MODE)
	/*
	 * STANDBY Mode Entry - Backup SRAM and RTC OFF - IWDG and LSI OFF - Wakeup using
	 * WakeUp Pin (PA.00)
	 */
	StandbyMode_Measure();
#elif defined(STANDBY_RTC_MODE)
	/*
	 * STANDBY Mode with RTC on LSI Entry - RTC Clocked by LSI - IWDG OFF and LSI OFF
	 * if not used as RTC Clock source - Backup SRAM OFF - Automatic Wakeup using RTC
	 * clocked by LSI (after ~20s)
	 */
	StandbyRTCMode_Measure();
#elif defined(STANDBY_RTC_BKPSRAM_MODE)
	/*
	 * STANDBY Mode with RTC on LSI Entry - RTC Clocked by LSI - Backup SRAM ON - IWDG
	 * OFF - Automatic Wakeup using RTC clocked by LSI (after ~20s)
	 */
	StandbyRTCBKPSRAMMode_Measure();

#else

	/* Infinite loop */
	while (1)
		{
			/* Toggle The LED4 */
			STM_EVAL_LEDToggle(LED3);
			STM_EVAL_LEDToggle(LED4);
			STM_EVAL_LEDToggle(LED5);
			STM_EVAL_LEDToggle(LED6);
			/* Inserted Delay */
			for (i = 0; i < 0x5FF; i++);
		}
#endif
	return 1;
}

#ifdef USE_FULL_ASSERT

/*
 =======================================================================================================================
    @brief Reports the name of the source file and the source line number where the assert_param error has occurred.
    @param file: pointer to the source file name @param line: assert_param error line source number @retval None
 =======================================================================================================================
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/*
	 * User can add his own implementation to report the file name and line number,
	 * ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) ;
	 * Infinite loop
	 */
	while (1) { }
}
#endif

/*
 * @} ;
 * @} ;
 * (C) COPYRIGHT 2011 STMicroelectronics END OF FILE
 */
