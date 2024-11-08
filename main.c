/******************************************************************************
* File Name: main.c
*
* Description: This is the source code for the FreeRTOS
*              LE Long Range Peripheral Example for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2021-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "stdio.h"
#include "wiced_bt_stack.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <string.h>
#include "wiced_memory.h"

#include "cyhal.h"
#include "stdio.h"
#include "GeneratedSource/cycfg_gatt_db.h"
#include "GeneratedSource/cycfg_bt_settings.h"
#include "GeneratedSource/cycfg_gap.h"
#include "wiced_bt_dev.h"
#include "app_bt_utils.h"
#include "hello_sensor.h"


/*******************************************************************************
*        Macro Definitions
*******************************************************************************/

/*******************************************************************************
* Variable Definitions
*******************************************************************************/

/******************************************************************************
 * Function Definitions
 ******************************************************************************/

/*******************************************************************************
 * Function Name : main
 * *****************************************************************************
 * Summary :
*   Entry point to the application. Set device configuration and start BT
 *  stack initialization.  The actual application initialization will happen
 *  when stack reports that BT device is ready.
 *
 * Parameters:
 *    None
 *
 * Return:
 *    None
 ******************************************************************************/
int main()
{
    cy_rslt_t cy_result;
    wiced_result_t wiced_result;

    /* Initialize the board support package */
    cy_result = cybsp_init();

    if (CY_RSLT_SUCCESS != cy_result)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    #ifdef ENABLE_BT_SPY_LOG
    {
        cybt_debug_uart_config_t config = {
            .uart_tx_pin = CYBSP_DEBUG_UART_TX,
            .uart_rx_pin = CYBSP_DEBUG_UART_RX,
            .uart_cts_pin = CYBSP_DEBUG_UART_CTS,
            .uart_rts_pin = CYBSP_DEBUG_UART_RTS,
            .baud_rate = DEBUG_UART_BAUDRATE,
            .flow_control = TRUE};
        cybt_debug_uart_init(&config, NULL);
    }
    #else
    {
        /* Initialize retarget-io to use the debug UART port */
        cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    }
    #endif //ENABLE_BT_SPY_LOG

    /* Enable global interrupts */
    __enable_irq();

    printf("==============================================\r\n");
    printf("Bluetooth LE-LR Peripheral\n");
    printf("===============================================\r\n\n");

    /* Create a buffer heap, make it the default heap.  */
    wiced_bt_create_heap("app", NULL, 0x1000, NULL, WICED_TRUE);

   /* Register call back and configuration with stack */
   wiced_result = wiced_bt_stack_init (hello_sensor_management_callback, &wiced_bt_cfg_settings);

   /* Check if stack initialization was successful */
   if( WICED_BT_SUCCESS == wiced_result)
   {
       printf("Bluetooth Stack Initialization Successful \n");
   }
   else
   {
       printf("Bluetooth Stack Initialization failed!! \n");
       CY_ASSERT(0);
   }
}


/* END OF FILE [] */
