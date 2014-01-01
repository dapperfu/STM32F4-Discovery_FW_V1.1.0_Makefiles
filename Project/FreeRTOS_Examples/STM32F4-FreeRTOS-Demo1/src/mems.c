
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "utils.h"
#include "debug.h"
#include "stm32f4_discovery_lis302dl.h"
#include "mems.h"

#define AVG_WEIGHT	5
int8_t accel[6];
int8_t s8buff[6];
uint8_t fMems_Debug = false;

enum accelAxis { xAxis, na1, yAxis, na2, zAxis, na3 };

#define GRN_LED	0x01
#define ORG_LED	0x02
#define RED_LED	0x04
#define	BLU_LED	0x08
#define MEMS_MULT	4


//extern portTASK_FUNCTION( vMemsTask, pvParameters );

// ----------------------------------------------------------------------------
portTASK_FUNCTION( vMemsTask, pvParameters ) {

    uint8_t ctrl = 0, i=0, j=0;

    LIS302DL_InitTypeDef  LIS302DL_InitStruct;
    LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;  

    /* Set configuration of LIS302DL*/
    LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
    LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
    LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
    LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
    LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
    LIS302DL_Init( &LIS302DL_InitStruct );

    /* Set configuration of Internal High Pass Filter of LIS302DL*/
    LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
    LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
    LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
    LIS302DL_InterruptConfig( &LIS302DL_InterruptStruct );

    /* Required delay for the MEMS Accelerometre: Turn-on time = 3/Output data Rate 
       = 3/100 = 30ms */
    vTaskDelay( 30 / portTICK_RATE_MS );

    /* Configure Interrupt control register: enable Click interrupt1 */
    ctrl = 0x07;
    LIS302DL_Write( &ctrl, LIS302DL_CTRL_REG3_ADDR, 1 );

    /* Enable Interrupt generation on click/double click on Z axis */
    ctrl = 0x70;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1 );

    /* Configure Click Threshold on X/Y axis (10 x 0.5g) */
    ctrl = 0xAA;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1 );

    /* Configure Click Threshold on Z axis (10 x 0.5g) */
    ctrl = 0x0A;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_THSZ_REG_ADDR, 1 );

    /* Configure Time Limit */
    ctrl = 0x03;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1 );

    /* Configure Latency */
    ctrl = 0x7F;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1 );

    /* Configure Click Window */
    ctrl = 0x7F;
    LIS302DL_Write( &ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1 );

    accel[xAxis] = 0;
    accel[yAxis] = 0;
    accel[zAxis] = 0;

    while ( 1 ) {
        vTaskDelay( 15 / portTICK_RATE_MS );
        LIS302DL_Read( (uint8_t*)s8buff, LIS302DL_OUT_X_ADDR, 5 );

        // Average reading.
        accel[xAxis] = (accel[xAxis] * AVG_WEIGHT + s8buff[xAxis]) / (AVG_WEIGHT + 1);
        accel[yAxis] = (accel[yAxis] * AVG_WEIGHT + s8buff[yAxis]) / (AVG_WEIGHT + 1);
        accel[zAxis] = (accel[zAxis] * AVG_WEIGHT + s8buff[zAxis]) / (AVG_WEIGHT + 1);

        // Update the LED every 45ms.
        if ( ++i >= 3 ) {
        	i = 0;
			if ( accel[xAxis] == 0 ) {
				TIM_SetDuty( TIM4, ORG_LED | BLU_LED, 0 );
			}
			else {
				if ( accel[xAxis] > 0 ) {
					TIM_SetDuty( TIM4, ORG_LED, ptopwm( accel[xAxis] * MEMS_MULT) );
					TIM_SetDuty( TIM4, BLU_LED, 0 );
				}
				else {
					TIM_SetDuty( TIM4, BLU_LED, ptopwm( accel[xAxis] * -MEMS_MULT) );
					TIM_SetDuty( TIM4, ORG_LED, 0 );
				}
			}


			if ( accel[yAxis] == 0 ) {
				TIM_SetDuty( TIM4, GRN_LED | RED_LED, 0 );
			}
			else {
				if ( accel[yAxis] > 0 ) {
					TIM_SetDuty( TIM4, GRN_LED, ptopwm( accel[yAxis] * MEMS_MULT) );
					TIM_SetDuty( TIM4, RED_LED, 0 );
				}
				else {
					TIM_SetDuty( TIM4, RED_LED, ptopwm( accel[yAxis] * -MEMS_MULT) );
					TIM_SetDuty( TIM4, GRN_LED, 0 );
				}
			}
        }

        // Send debug string every 180ms.
        if ( fMems_Debug & (++j >= 12) ) {
        	j = 0;
            vDebugPrintf( "Accel %i %i %i\n", accel[xAxis], accel[yAxis], accel[zAxis] );
        }
    }
}

// ----------------------------------------------------------------------------
void vSetMemsDump( uint8_t flg ) {
	fMems_Debug = flg;
}

// The Mems dirver calls this on a timeout while waiting for a memes response.
// ----------------------------------------------------------------------------
uint32_t LIS302DL_TIMEOUT_UserCallback( void ) {
    configASSERT( 0 );  // Latch on error.
    return 0;
}

